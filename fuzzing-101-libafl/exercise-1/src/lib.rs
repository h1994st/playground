use libafl::bolts::current_nanos;
use libafl::bolts::rands::StdRand;
use libafl::bolts::tuples::tuple_list;
use libafl::corpus::{
    Corpus, InMemoryCorpus, IndexesLenTimeMinimizerCorpusScheduler, OnDiskCorpus,
    QueueCorpusScheduler,
};
use libafl::events::{setup_restarting_mgr_std, EventConfig, EventRestarter};
use libafl::executors::{ExitKind, InProcessExecutor, TimeoutExecutor};
use libafl::feedbacks::{MapFeedbackState, MaxMapFeedback, TimeFeedback, TimeoutFeedback};
use libafl::inputs::{BytesInput, HasTargetBytes};
use libafl::monitors::MultiMonitor;
use libafl::mutators::{havoc_mutations, StdScheduledMutator};
use libafl::observers::{HitcountsMapObserver, StdMapObserver, TimeObserver};
use libafl::stages::StdMutationalStage;
use libafl::state::{HasCorpus, StdState};
use libafl::{feedback_and_fast, feedback_or, Error, Fuzzer, StdFuzzer};
use libafl_targets::{libfuzzer_test_one_input, EDGES_MAP, MAX_EDGES_NUM};
use std::path::PathBuf;
use std::time::Duration;

#[no_mangle]
fn libafl_main() -> Result<(), Error> {
    // - Corpus
    // inputs
    let corpus_dirs = vec![PathBuf::from("./corpus")];
    let input_corpus = InMemoryCorpus::<BytesInput>::new();

    // outputs
    let timeouts_corpus =
        OnDiskCorpus::new(PathBuf::from("./timeouts")).expect("Couldn't create timeouts corpus");

    // - Observer
    // time
    let time_observer = TimeObserver::new("time");

    // coverage
    let edges = unsafe { &mut EDGES_MAP[0..MAX_EDGES_NUM] };
    let edges_observer = HitcountsMapObserver::new(StdMapObserver::new("edges", edges));

    // - feedback
    let feedback_state = MapFeedbackState::with_observer(&edges_observer);
    let feedback = feedback_or!(
        MaxMapFeedback::new_tracking(&feedback_state, &edges_observer, true, false),
        TimeFeedback::new_with_observer(&time_observer)
    );
    let objective_state = MapFeedbackState::new("timeout_edges", unsafe { EDGES_MAP.len() });
    let objective = feedback_and_fast!(
        TimeoutFeedback::new(),
        MaxMapFeedback::new(&objective_state, &edges_observer)
    );

    // - monitor
    let monitor = MultiMonitor::new(|s| println!("{}", s));

    // - event manager
    let (state, mut mgr) = match setup_restarting_mgr_std(monitor, 1337, EventConfig::AlwaysUnique)
    {
        Ok(res) => res,
        Err(err) => match err {
            Error::ShuttingDown => {
                return Ok(());
            }
            _ => {
                panic!("Failed to setup the restarting manager: {}", err);
            }
        },
    };

    // - state
    let mut state = state.unwrap_or_else(|| {
        StdState::new(
            StdRand::with_seed(current_nanos()),
            input_corpus,
            timeouts_corpus,
            tuple_list!(feedback_state, objective_state),
        )
    });

    // - scheduler
    let scheduler = IndexesLenTimeMinimizerCorpusScheduler::new(QueueCorpusScheduler::new());

    // - fuzzer
    let mut fuzzer = StdFuzzer::new(scheduler, feedback, objective);

    // - harness
    let mut harness = |input: &BytesInput| {
        let target = input.target_bytes();
        let buffer = target.as_slice();
        libfuzzer_test_one_input(buffer);
        ExitKind::Ok
    };

    // - executor
    let in_proc_executor = InProcessExecutor::new(
        &mut harness,
        tuple_list!(edges_observer, time_observer),
        &mut fuzzer,
        &mut state,
        &mut mgr,
    )
    .expect("Couldn't create the in-process executor");
    let timeout = Duration::from_millis(5000);
    let mut executor = TimeoutExecutor::new(in_proc_executor, timeout);

    // load initial test cases
    if state.corpus().count() < 1 {
        state
            .load_initial_inputs(&mut fuzzer, &mut executor, &mut mgr, &corpus_dirs)
            .unwrap_or_else(|err| {
                panic!(
                    "Failed to load initial corpus at {:?}: {:?}",
                    &corpus_dirs, err
                );
            });
        println!("Loaded {} inputs from disk.", state.corpus().count());
    }

    // - mutator & stage
    let mutator = StdScheduledMutator::new(havoc_mutations());
    let mut stages = tuple_list!(StdMutationalStage::new(mutator));

    // here we go!
    fuzzer
        .fuzz_loop_for(&mut stages, &mut executor, &mut state, &mut mgr, 10000)
        .expect("Error in the fuzzing loop");

    mgr.on_restart(&mut state).expect("Couldn't restart");

    Ok(())
}

use libafl::bolts::current_nanos;
use libafl::bolts::rands::StdRand;
use libafl::bolts::shmem::{ShMem, ShMemProvider, StdShMemProvider};
use libafl::bolts::tuples::tuple_list;
use libafl::corpus::{
    Corpus, InMemoryCorpus, IndexesLenTimeMinimizerCorpusScheduler, OnDiskCorpus,
    QueueCorpusScheduler,
};
use libafl::events::SimpleEventManager;
use libafl::executors::{ForkserverExecutor, TimeoutForkserverExecutor};
use libafl::feedbacks::{MapFeedbackState, MaxMapFeedback, TimeFeedback, TimeoutFeedback};
use libafl::inputs::BytesInput;
use libafl::mutators::{havoc_mutations, StdScheduledMutator};
use libafl::observers::{ConstMapObserver, HitcountsMapObserver, TimeObserver};
use libafl::stages::StdMutationalStage;
use libafl::state::{HasCorpus, StdState};
use libafl::stats::SimpleStats;
use libafl::{feedback_and_fast, feedback_or, Fuzzer, StdFuzzer};
use std::path::PathBuf;
use std::time::Duration;

const MAP_SIZE: usize = 65535;

fn main() {
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
    let mut shmem = StdShMemProvider::new().unwrap().new_map(MAP_SIZE).unwrap();
    shmem
        .write_to_env("__AFL_SHM_ID")
        .expect("Couldn't write shared memory ID");
    let mut shmem_map = shmem.map_mut();
    let edges_observer = HitcountsMapObserver::new(ConstMapObserver::<_, MAP_SIZE>::new(
        "shared_mem",
        &mut shmem_map,
    ));

    // - feedback
    let feedback_state = MapFeedbackState::with_observer(&edges_observer);
    let feedback = feedback_or!(
        MaxMapFeedback::new_tracking(&feedback_state, &edges_observer, true, false),
        TimeFeedback::new_with_observer(&time_observer)
    );
    let objective_state = MapFeedbackState::new("timeout_edges", MAP_SIZE);
    let objective = feedback_and_fast!(
        TimeoutFeedback::new(),
        MaxMapFeedback::new(&objective_state, &edges_observer)
    );

    // - state
    let mut state = StdState::new(
        StdRand::with_seed(current_nanos()),
        input_corpus,
        timeouts_corpus,
        tuple_list!(feedback_state, objective_state),
    );

    // - stats
    let stats = SimpleStats::new(|s| println!("{}", s));

    // - event manager
    let mut mgr = SimpleEventManager::new(stats);

    // - scheduler
    let scheduler = IndexesLenTimeMinimizerCorpusScheduler::new(QueueCorpusScheduler::new());

    // - fuzzer
    let mut fuzzer = StdFuzzer::new(scheduler, feedback, objective);

    // - executor
    let fork_server = ForkserverExecutor::new(
        "./xpdf/install/bin/pdftotext".to_string(),
        &[String::from("@@")],
        false,
        tuple_list!(edges_observer, time_observer),
    )
    .expect("Couldn't create the fork server");
    let timeout = Duration::from_millis(5000);
    let mut executor = TimeoutForkserverExecutor::new(fork_server, timeout)
        .expect("Couldn't create the timeout fork server");

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
        .fuzz_loop(&mut stages, &mut executor, &mut state, &mut mgr)
        .expect("Error in the fuzzing loop");
}

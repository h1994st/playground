use libafl_cc::{ClangWrapper, CompilerWrapper};
use std::env;

pub fn main() {
    let mut dir = env::current_exe().unwrap();
    let args: Vec<String> = env::args().collect();
    let mut cc = ClangWrapper::new();
    dir.pop();

    if let Some(code) = cc
        .cpp(false)
        // silence the compiler wrapper output, needed for some configure scripts.
        .silence(true)
        .from_args(&args)
        .expect("Failed to parse the command line")
        .link_staticlib(&dir, "exercisetwo")
        .add_arg("-fsanitize-coverage=trace-pc-guard")
        .add_arg("-fsanitize=address")
        .run()
        .expect("Failed to run the wrapped compiler")
    {
        std::process::exit(code);
    }
}

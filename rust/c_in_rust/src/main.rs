use libafl_bolts::os::{fork, ForkResult};

extern "C" {
    fn bar();
}

fn main() {
    let mut handles = vec![];

    match unsafe { fork().expect("Cannot fork") } {
        ForkResult::Parent(child) => {
            println!("child spawned {:?}", child);
            handles.push(child.pid);
        }
        ForkResult::Child => {
            println!("Child pid: {:?}", unsafe { libc::getpid() });
            std::thread::sleep(std::time::Duration::from_millis(3000));
            unsafe {
                bar();
            }
        }
    };

    for handle in &handles {
        let mut status = 0;
        unsafe {
            libc::waitpid(*handle, &mut status, 0);
            if status != 0 {
                println!("Child with pid {} exited with status {}", handle, status);
            }
        }
    }
}

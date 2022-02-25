extern "C" {
    fn bar();
}

fn main() {
    unsafe {
        bar();
    }
    println!("hahah");
}

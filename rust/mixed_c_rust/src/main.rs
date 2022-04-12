extern "C" {
    pub static mut objects: [u8; 16];
    pub static mut objects_size: usize;

    fn baz();
}

fn main() {
    unsafe {
        println!("{:?}", objects);
        baz();
        println!("{:?}", objects);

        let objects_ref = &objects;
        let objects_ptr = objects_ref as *const u8;
        println!("{:p}", objects_ptr);
    };
}

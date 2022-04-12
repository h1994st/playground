fn main() {
    println!("cargo:rerun-if-changed=src/foo.c");
    cc::Build::new().file("src/foo.c").compile("foo");

    println!("cargo:rerun-if-changed=src/bar.c");
    cc::Build::new().file("src/bar.c").compile("bar");

    println!("cargo:rerun-if-changed=build.rs");
}

fn main() {
    println!("cargo:rerun-if-changed=src/foo.c");
    cc::Build::new().file("src/foo.c").compile("libfoo");

    println!("cargo:rerun-if-changed=build.rs");
}

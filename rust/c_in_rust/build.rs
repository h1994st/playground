fn main() {
    println!("cargo:rerun-if-changed=src/foo.c");
    cc::Build::new()
        .file("src/foo.c")
        .include("/usr/local/cuda/include")
        .compile("libfoo");
    println!("cargo:rustc-link-lib=dylib=cuda");
    println!("cargo:rustc-link-lib=dylib=cudart");
    println!("cargo:rustc-link-search=native=/usr/local/cuda/lib64");

    println!("cargo:rerun-if-changed=build.rs");
}

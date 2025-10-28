# preimage-rs

A Rust program that finds SHA-1 hash preimages with specified trailing bytes. The program performs a parallel search to find an input string that, when hashed with SHA-1, results in a hash ending with a specified number of 0xFF bytes.

## Features

- Parallel search using Rayon for improved performance
- Configurable search for any number of trailing 0xFF bytes
- Searches through alphanumeric characters (0-9, a-z, A-Z)
- Input lengths from 1 to 15 characters
- Reports execution time

## Usage

First, build the program:

```bash
cargo build
cargo build --release
```

Run the program using Cargo:

```bash
cargo run [n]
```

where `n` is an optional parameter specifying the number of trailing 0xFF bytes to search for. If not provided, it defaults to 1.

### Example

Search for an input that produces a SHA-1 hash ending in two 0xFF bytes

```console
$ cargo build --release
...
$ ./target/release/preimage-rs 4
Searching for input with sha1 hash ending in 4 bytes of trailing 0xff
Elapsed time: 91.79s
Found matching input: "pXV8s"
sha1("pXV8s") = c0235fa2b3358fbc459b4d72d2fbd9baffffffff
```

## Implementation Details

The program:

1. Generates candidate strings using alphanumeric characters
2. Uses parallel iterator (par_bridge) from Rayon for concurrent processing
3. Calculates SHA-1 hash for each candidate
4. Checks if the hash ends with the specified number of 0xFF bytes
5. Reports the first matching input found along with its hash

## Dependencies

- `sha1`: For SHA-1 hash computation
- `rayon`: For parallel processing
- `itertools`: For cartesian product of character combinations

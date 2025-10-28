use itertools::{Itertools, repeat_n};
use rayon::prelude::*;
use sha1::{Digest, Sha1};
use std::{env::args, time::Instant};

fn main() {
    // Take `n` from user-provided argument or default to 1
    let n = args()
        .nth(1)
        .and_then(|arg| arg.parse::<usize>().ok())
        .unwrap_or(1);
    let target_hash = vec![0xff; n];

    println!(
        "Searching for input with sha1 hash ending in {} bytes of trailing 0xff",
        n
    );

    let candidate_chars = ('0'..='9')
        .chain('a'..='z')
        .chain('A'..='Z')
        .map(|x| x as u8)
        .collect::<Vec<_>>();

    let candidates =
        (1..16).flat_map(|len| repeat_n(candidate_chars.to_owned(), len).multi_cartesian_product());

    // Check the start time
    let start_time = Instant::now();

    let result = candidates.par_bridge().find_any(|candidate| {
        let hash = Sha1::digest(candidate);
        hash.ends_with(&target_hash)
    });

    // Measure elapsed time
    let elapsed = start_time.elapsed();
    println!("Elapsed time: {:.2?}", elapsed);

    if let Some(candidate) = result {
        let hash = Sha1::digest(&candidate);
        let candidate_str: String = candidate.iter().map(|&x| x as char).collect();
        println!("Found matching input: {:?}", candidate_str);
        println!("sha1({:?}) = {:x}", candidate_str, hash);
    } else {
        println!("No matching input found.");
    }
}

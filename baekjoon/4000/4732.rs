use std::io::*;

fn main() {
    const A: [&str; 12] = ["A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"];
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut it = s.split('\n');
    loop {
        let s = it.next().unwrap();
        if s == "***" {
            break;
        }
        let ids = s
            .split_ascii_whitespace()
            .map(|word| {
                word.chars().fold(0, |i, c| match c {
                    'A' => 0,
                    'B' => 2,
                    'C' => 3,
                    'D' => 5,
                    'E' => 7,
                    'F' => 8,
                    'G' => 10,
                    '#' => i + 1,
                    'b' => i - 1,
                    _ => unreachable!(),
                })
            })
            .collect::<Vec<_>>();
        let d = it.next().unwrap().parse::<i32>().unwrap();
        for i in ids {
            print!("{} ", A[((i + 12 + d) as usize) % 12]);
        }
        println!();
    }
}

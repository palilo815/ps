use std::io::*;

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut it = s.split('\n');
    let t = it.next().unwrap().parse::<usize>().unwrap();
    for t in 1..=t {
        print!("Case #{t}:");
        for word in it.next().unwrap().split_ascii_whitespace().rev() {
            print!(" {word}");
        }
        println!();
    }
}

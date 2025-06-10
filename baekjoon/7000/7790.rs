use std::io::*;

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let ans = s.split_ascii_whitespace().map(|s| s.matches("joke").count()).sum::<usize>();
    println!("{ans}");
}

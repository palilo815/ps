use std::io::*;

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut it = s.split_ascii_whitespace();
    const IGNORE: [&str; 10] = ["i", "pa", "te", "ni", "niti", "a", "ali", "nego", "no", "ili"];
    let first = it.next().unwrap().bytes().next().unwrap();
    let other = it.filter_map(|s| if IGNORE.contains(&s) { None } else { s.bytes().next() });
    let ans = std::iter::once(first).chain(other).collect::<Vec<_>>();
    println!("{}", String::from_utf8(ans).unwrap().to_uppercase());
}

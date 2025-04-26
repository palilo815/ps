use std::io::*;

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut ans = 0_u64;
    for s in s.leak().split(|c: char| !c.is_ascii_digit()) {
        let mut pref = [1, 0, 0];
        let mut acc = 0;
        for c in s.bytes() {
            acc = (acc + c as usize) % 3;
            ans += pref[acc];
            pref[acc] += 1;
        }
    }
    println!("{ans}");
}

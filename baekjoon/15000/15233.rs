use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_array<const N: usize>(&mut self) -> [u8; N] {
        let s = self.it.next().unwrap();
        let mut a = [0; N];
        a[..s.len()].copy_from_slice(s.as_bytes());
        a
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let a = (0..n).map(|_| sc.read_array::<20>()).collect::<Vec<_>>();
    let b = (0..m).map(|_| sc.read_array::<20>()).collect::<Vec<_>>();
    let mut diff = 0;
    for _ in 0..k {
        let s = sc.read_array::<20>();
        if a.contains(&s) {
            diff += 1;
        } else if b.contains(&s) {
            diff -= 1;
        } else {
            unreachable!();
        }
    }
    let ans = match diff.cmp(&0) {
        std::cmp::Ordering::Greater => "A",
        std::cmp::Ordering::Less => "B",
        _ => "TIE",
    };
    writeln!(bw, "{ans}").ok();
}

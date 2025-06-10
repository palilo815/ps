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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const DAYS: [usize; 12] = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
    const DAY: [&str; 7] = ["MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"];
    let m = sc.read::<usize>();
    let d = sc.read::<usize>() + DAYS.iter().take(m - 1).sum::<usize>();
    writeln!(bw, "{}", DAY[(d - 1) % 7]).ok();
}

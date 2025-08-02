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
    let a = (0..18).map(|_| sc.read::<usize>()).collect::<Vec<_>>();
    let b = (0..18).map(|_| sc.read::<usize>()).collect::<Vec<_>>();
    let mut score_a = [0; 12];
    let mut score_b = [0; 12];
    score_a[0] = a.iter().sum::<usize>();
    for x in a {
        score_a[11 - x] += 1;
    }
    score_b[0] = b.iter().sum::<usize>();
    for x in b {
        score_b[11 - x] += 1;
    }
    let ans = match score_a.cmp(&score_b) {
        std::cmp::Ordering::Greater => "Algosia",
        std::cmp::Ordering::Less => "Bajtek",
        _ => "remis",
    };
    writeln!(bw, "{ans}").ok();
}

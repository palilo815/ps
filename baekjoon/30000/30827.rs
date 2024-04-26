use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut end = [0; 3];
    let mut meetings = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    meetings.sort_unstable_by(|l, r| l.1.cmp(&r.1));
    let mut ans = 0;
    for (s, e) in meetings {
        if let Some(x) = end.iter_mut().take(k).filter(|x| **x < s).max() {
            *x = e;
            ans += 1;
        }
    }
    writeln!(bw, "{ans}").ok();
}

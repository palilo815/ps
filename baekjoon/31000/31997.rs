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
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let t = sc.read::<usize>();
    let inout = (0..n).map(|_| (sc.read::<usize>(), sc.read::<usize>())).collect::<Vec<_>>();
    let mut pref = vec![0; t + 1];
    for _ in 0..m {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        if inout[u].1 <= inout[v].0 || inout[v].1 <= inout[u].0 {
            continue;
        }
        pref[inout[u].0.max(inout[v].0)] += 1;
        pref[inout[u].1.min(inout[v].1)] -= 1;
    }
    for i in 0..t {
        pref[i + 1] += pref[i];
    }
    for x in pref.into_iter().take(t) {
        writeln!(bw, "{x}").ok();
    }
}

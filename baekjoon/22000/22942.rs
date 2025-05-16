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
    let mut a = vec![(0, 0); 2 * n];
    for i in 0..n {
        let x = sc.read::<i32>();
        let r = sc.read::<i32>();
        a[i << 1] = (x - r, !(i as i32));
        a[i << 1 | 1] = (x + r, i as i32);
    }
    a.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    if a.windows(2).any(|w| w[0].0 == w[1].0) {
        writeln!(bw, "NO").ok();
        return;
    }
    let mut stack = Vec::with_capacity(n);
    for (x, i) in a {
        if i < 0 {
            stack.push((x, !i));
        } else if !stack.pop().is_some_and(|(_, j)| i == j) {
            writeln!(bw, "NO").ok();
            return;
        }
    }
    writeln!(bw, "YES").ok();
}

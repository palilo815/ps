use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = Vec::new();
        stdin().lock().read_to_end(&mut buf).ok();
        let s = unsafe { std::str::from_utf8_unchecked(Box::leak(buf.into_boxed_slice())) };
        Self { it: s.split_ascii_whitespace() }
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
    let mut c = (1..=k).map(|i| (i, sc.read::<usize>())).collect::<Vec<_>>();
    c.sort_unstable_by(|l, r| r.1.cmp(&l.1));
    if c[0].1 > n.div_ceil(2) || c.iter().fold(0, |acc, x| acc + x.1) != n {
        writeln!(bw, "-1").ok();
        return;
    }
    let mut ans = vec![0; n];
    let mut i = 0;
    for x in ans.iter_mut().step_by(2) {
        *x = c[i].0;
        c[i].1 -= 1;
        if c[i].1 == 0 {
            i += 1;
        }
    }
    for x in ans.iter_mut().skip(1).step_by(2) {
        *x = c[i].0;
        c[i].1 -= 1;
        if c[i].1 == 0 {
            i += 1;
        }
    }
    for x in ans {
        write!(bw, "{x} ").ok();
    }
}

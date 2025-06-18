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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let c = sc.read::<usize>();
    let n = sc.read::<usize>();
    let mut a = sc.read_vec::<usize>(c);
    a.sort_unstable();
    let mut fire = vec![false; n + 1];
    for x in a {
        if !fire[x] {
            fire.iter_mut().skip(x).step_by(x).for_each(|f| *f = true);
        }
    }
    let ans = fire.into_iter().filter(|&f| f).count();
    writeln!(bw, "{ans}").ok();
}

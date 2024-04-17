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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let q = sc.read::<usize>();
    let mut deadline = sc.read_vec::<i32>(n);
    deadline.iter_mut().for_each(|x| *x -= sc.read::<i32>());
    deadline.sort_unstable_by(|l, r| r.cmp(l));
    for _ in 0..q {
        let v = sc.read::<usize>();
        let s = sc.read::<i32>();
        writeln!(bw, "{}", if deadline[v - 1] > s { "YES" } else { "NO" }).ok();
    }
}

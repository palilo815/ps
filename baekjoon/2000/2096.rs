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
    let mut lo = [0; 3];
    let mut hi = [0; 3];
    for _ in 0..n {
        let score = [sc.read::<i32>(), sc.read::<i32>(), sc.read::<i32>()];
        let l = lo[0].min(lo[1]);
        let r = lo[2].min(lo[1]);
        lo[0] = score[0] + l;
        lo[1] = score[1] + l.min(r);
        lo[2] = score[2] + r;
        let l = hi[0].max(hi[1]);
        let r = hi[2].max(hi[1]);
        hi[0] = score[0] + l;
        hi[1] = score[1] + l.max(r);
        hi[2] = score[2] + r;
    }
    let lo = lo.into_iter().min().unwrap();
    let hi = hi.into_iter().max().unwrap();
    writeln!(bw, "{hi} {lo}").ok();
}


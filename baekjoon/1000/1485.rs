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
    let t = sc.read::<usize>();
    let mut p = [(0, 0); 4];
    let dist = |p: (i64, i64), q: (i64, i64)| -> i64 { (p.0 - q.0) * (p.0 - q.0) + (p.1 - q.1) * (p.1 - q.1) };
    for _ in 0..t {
        for (x, y) in p.iter_mut() {
            *x = sc.read();
            *y = sc.read();
        }
        let d01 = dist(p[0], p[1]);
        let d02 = dist(p[0], p[2]);
        if d01 == d02 {
            p.swap(2, 3);
        } else if d01 > d02 {
            p.swap(1, 2)
        }
        let d01 = dist(p[0], p[1]);
        let d12 = dist(p[1], p[2]);
        let d23 = dist(p[2], p[3]);
        let d30 = dist(p[3], p[0]);
        let d02 = dist(p[0], p[2]);
        let ans = (d01 == d12 && d12 == d23 && d23 == d30 && d01 * 2 == d02) as i32;
        writeln!(bw, "{ans}").ok();
    }
}

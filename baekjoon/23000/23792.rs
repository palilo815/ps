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

fn solve(a: &[u32], b: &[u32], c: &[u32], k: usize) -> Option<usize> {
    let mut lo = 0;
    let mut hi = a.len();
    while lo != hi {
        let mid = (lo + hi) >> 1;
        let rank = 1 + mid + b.partition_point(|&x| x < a[mid]) + c.partition_point(|&x| x < a[mid]);
        match rank.cmp(&k) {
            std::cmp::Ordering::Less => lo = mid + 1,
            std::cmp::Ordering::Greater => hi = mid,
            _ => return Some(mid + 1),
        }
    }
    None
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let a = sc.read_vec::<u32>(n);
    let b = sc.read_vec::<u32>(n);
    let c = sc.read_vec::<u32>(n);
    let q = sc.read::<usize>();
    for _ in 0..q {
        let a = &a[..sc.read::<usize>()];
        let b = &b[..sc.read::<usize>()];
        let c = &c[..sc.read::<usize>()];
        let k = sc.read::<usize>();
        let (x, y) = solve(a, b, c, k).map_or_else(
            || solve(b, c, a, k).map_or_else(|| (3, solve(c, a, b, k).unwrap()), |y| (2, y)),
            |y| (1, y),
        );
        writeln!(bw, "{x} {y}").ok();
    }
}

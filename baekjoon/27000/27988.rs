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
    let n = sc.read::<usize>();
    let x = sc.read_vec::<i32>(n);
    let l = sc.read_vec::<u32>(n);
    let mut last_r = usize::MAX;
    let mut last_y = usize::MAX;
    let mut last_b = usize::MAX;
    for i in 0..n {
        let (i2, j, k) = match sc.read::<char>() {
            'R' => (&mut last_r, last_y, last_b),
            'Y' => (&mut last_y, last_b, last_r),
            _ => (&mut last_b, last_r, last_y),
        };
        if j != usize::MAX && (x[i].abs_diff(x[j]) <= l[i] + l[j]) {
            writeln!(bw, "YES").ok();
            writeln!(bw, "{} {}", j + 1, i + 1).ok();
            return;
        }
        if k != usize::MAX && (x[i].abs_diff(x[k]) <= l[i] + l[k]) {
            writeln!(bw, "YES").ok();
            writeln!(bw, "{} {}", k + 1, i + 1).ok();
            return;
        }
        if *i2 == usize::MAX || x[*i2] + (l[*i2] as i32) < x[i] + (l[i] as i32) {
            *i2 = i;
        }
    }
    writeln!(bw, "NO").ok();
}

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
    let mut a = sc.read_vec::<i32>(n);
    let mut vals = a.clone();
    vals.sort_unstable();
    for x in a.iter_mut() {
        *x = vals.partition_point(|v| v < x) as i32;
    }
    let mut ans = 0;
    for i in 0..n {
        while i != a[i] as usize {
            let j = a[i] as usize;
            a.swap(i, j);
            ans += 1;
        }
    }
    writeln!(bw, "{ans}").ok();
}

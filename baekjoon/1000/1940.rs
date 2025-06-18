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
    let m = sc.read::<i32>();
    let mut a = sc.read_vec::<i32>(n);
    a.sort_unstable();
    let mut ans = 0;
    let mut j = n - 1;
    for i in 0..n {
        while i < j && a[i] + a[j] > m {
            j -= 1;
        }
        if i >= j {
            break;
        }
        if a[i] + a[j] == m {
            ans += 1;
            j -= 1;
        }
    }
    writeln!(bw, "{ans}").ok();
}

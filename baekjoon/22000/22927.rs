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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let a = sc.read_vec::<u32>(n);
    let mut ans = 1;
    let mut r = 1;
    while r < n - 1 {
        let mut l = r;
        while l != 0 && r != n - 1 && a[l - 1] < a[l] && a[l - 1] == a[r + 1] {
            l -= 1;
            r += 1;
        }
        ans = ans.max(r - l + 1);
        r += 1;
    }
    writeln!(bw, "{}", if ans == 1 { -1 } else { ans as i32 }).ok();
}

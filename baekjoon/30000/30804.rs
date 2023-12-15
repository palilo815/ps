use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
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
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let a = sc.read_vec::<usize>(n);
    let mut cnt = [0; 10];
    let mut kind = 0;
    let mut ans = 0;
    let mut l = 0;
    for (r, &x) in a.iter().enumerate() {
        kind += (cnt[x] == 0) as i32;
        cnt[x] += 1;
        while kind > 2 {
            cnt[a[l]] -= 1;
            kind -= (cnt[a[l]] == 0) as i32;
            l += 1;
        }
        ans = ans.max(r - l + 1);
    }
    writeln!(out, "{}", ans).ok();
}

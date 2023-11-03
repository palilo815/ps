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
    let k = sc.read::<usize>();
    let mut a = sc.read_vec::<usize>(n);
    let mut ans = 0;
    let mut i = 0;
    let mut j = 0;
    loop {
        while i != n && a[i] <= k {
            i += 1;
        }
        if i == n {
            break;
        }
        while a[j] >= k {
            j += 1;
        }
        let moved = (a[i] - k).min(k - a[j]);
        a[i] -= moved;
        a[j] += moved;
        ans += moved * i.abs_diff(j);
    }
    writeln!(out, "{ans}").ok();
}

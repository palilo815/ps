use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
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
    let a = sc.read_vec::<u64>(n);
    let (mut i, mut j, mut k) = (0, 1, 2);
    let (mut x, mut y, mut z) = (a[0], a[1], a.iter().skip(2).sum::<u64>());
    let mut ans = 0;
    loop {
        let mn = x.min(y.min(z));
        ans = ans.max(mn);
        if x == mn {
            x += a[j];
            y -= a[j];
            j = if j + 1 == n { 0 } else { j + 1 };
        } else if y == mn {
            y += a[k];
            z -= a[k];
            k = if k + 1 == n { 0 } else { k + 1 };
        } else {
            z += a[i];
            x -= a[i];
            i = if i + 1 == n { 0 } else { i + 1 };
            if i == 0 {
                break;
            }
        }
    }
    writeln!(out, "{ans}").ok();
}

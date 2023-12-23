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
    let mut a = sc.read_vec::<usize>(n);
    let mut ans = 0;
    for p in (0..61).rev() {
        let i = a.iter().enumerate().max_by(|l, r| l.1.cmp(r.1)).unwrap().0;
        if a[i] >> p & 1 == 0 {
            continue;
        }
        let mx = a.swap_remove(i);
        if ans >> p & 1 == 0 {
            ans ^= mx;
        }
        for x in a.iter_mut() {
            if *x >> p & 1 == 1 {
                *x ^= mx;
            }
        }
        if a.is_empty() {
            break;
        }
    }
    writeln!(out, "{ans}").ok();
}

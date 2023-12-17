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
    let a = sc.read_vec::<i64>(n);
    let mut dp = vec![0; n];
    let mut tp = vec![0; n];
    for k in 0..n {
        std::mem::swap(&mut dp, &mut tp);
        if (n - k) & 1 == 0 {
            // IOI turn
            dp.iter_mut()
                .enumerate()
                .for_each(|(i, x)| *x = if a[i] > a[(i + k) % n] { tp[(i + 1) % n] } else { tp[i] });
        } else {
            // JOI rutn
            dp.iter_mut()
                .enumerate()
                .for_each(|(i, x)| *x = (a[i] + tp[(i + 1) % n]).max(a[(i + k) % n] + tp[i]));
        }
    }
    writeln!(out, "{}", dp.into_iter().max().unwrap()).ok();
}


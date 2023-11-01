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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    const N: usize = 200_000;
    let mut a = vec![0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        for x in a.iter_mut() {
            *x = sc.read::<i64>();
        }
        let sum_diff = a.windows(2).fold(0, |acc, w| acc + w[0].abs_diff(w[1]));
        let best = a.windows(3).fold(a[0].abs_diff(a[1]).max(a[n - 1].abs_diff(a[n - 2])), |best, w| {
            best.max(w[0].abs_diff(w[1]) + w[1].abs_diff(w[2]) - w[2].abs_diff(w[0]))
        });
        writeln!(out, "{}", sum_diff - best).ok();
    }
}

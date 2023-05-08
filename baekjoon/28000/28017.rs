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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut dp = vec![0; m];
    let mut tp = vec![0; m];
    for _ in 0..n {
        std::mem::swap(&mut dp, &mut tp);
        let init = if tp[0] < tp[1] { (0, 1) } else { (1, 0) };
        let best = tp.iter().enumerate().skip(2).fold(init, |best2, (i, &x)| {
            if x < tp[best2.0] {
                (i, best2.0)
            } else if x < tp[best2.1] {
                (best2.0, i)
            } else {
                best2
            }
        });
        for (i, x) in dp.iter_mut().enumerate() {
            *x = if i == best.0 { tp[best.1] } else { tp[best.0] } + sc.read::<u32>();
        }
    }
    writeln!(out, "{}", dp.into_iter().min().unwrap()).ok();
}

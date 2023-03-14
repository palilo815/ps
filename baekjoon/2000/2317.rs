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
    let k = sc.read::<usize>();
    let lions = sc.read_vec::<i32>(k);
    let mut acc = lions.windows(2).fold(0, |acc, w| acc + (w[0] - w[1]).abs());
    if n == k {
        writeln!(out, "{acc}").ok();
        return;
    }
    let mn = *lions.iter().min().unwrap();
    let mx = *lions.iter().max().unwrap();
    let (peek_mn, peek_mx) = (k..n).fold((i32::MAX, i32::MIN), |(mn, mx), _| {
        let x = sc.read::<i32>();
        (mn.min(x), mx.max(x))
    });
    acc += ((mn - peek_mn).max(0) * 2).min((lions[0].min(lions[k - 1]) - peek_mn).abs());
    acc += ((peek_mx - mx).max(0) * 2).min((lions[0].max(lions[k - 1]) - peek_mx).abs());
    writeln!(out, "{acc}").ok();
}

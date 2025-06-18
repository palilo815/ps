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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let l = sc.read::<usize>();
    let n = sc.read::<usize>();
    let mut check = vec![false; l];
    let a = (0..n)
        .map(|_| {
            let l = sc.read::<usize>() - 1;
            let r = sc.read::<usize>();
            let mut acc = 0;
            for x in &mut check[l..r] {
                if !*x {
                    acc += 1;
                    *x = true;
                }
            }
            (r - l, acc)
        })
        .collect::<Vec<_>>();
    let (expected, _) = a.iter().enumerate().rev().max_by(|l, r| l.1.0.cmp(&r.1.0)).unwrap();
    let (actual, _) = a.iter().enumerate().rev().max_by(|l, r| l.1.1.cmp(&r.1.1)).unwrap();
    writeln!(bw, "{}\n{}", expected + 1, actual + 1).ok();
}

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
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<u32>();
    let sx = sc.read::<i64>();
    let sy = sc.read::<i64>();
    let ex = sc.read::<i64>();
    let ey = sc.read::<i64>();
    let ans = (0..n)
        .map(|i| {
            let m = sc.read::<usize>();
            let res = (0..m).fold((0, sx, sy), |acc, _| {
                let x = sc.read::<i64>();
                let y = sc.read::<i64>();
                (acc.0 + (x - acc.1).abs() + (y - acc.2).abs(), x, y)
            });
            (i, res.0 + (ex - res.1).abs() + (ey - res.2).abs())
        })
        .max_by(|lhs, rhs| rhs.1.cmp(&lhs.1))
        .unwrap()
        .0;
    writeln!(out, "{}", ans + 1).ok();
}

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
    let m = sc.read::<usize>();
    let n = sc.read::<usize>();
    let mut g = (0..m)
        .map(|_| (sc.read::<i32>(), sc.read::<i32>(), sc.read::<i32>()))
        .collect::<Vec<_>>();
    g.sort_unstable_by(|l, r| l.2.cmp(&r.2));
    let ans = (0..n).fold(0, |acc, _| {
        let x = sc.read::<i32>();
        let y = sc.read::<i32>();
        let t = sc.read::<i32>();
        let i = g.partition_point(|p| p.2 < t);
        let f0 = if i == 0 {
            false
        } else {
            let dx = (x - g[i - 1].0) as i64;
            let dy = (y - g[i - 1].1) as i64;
            let dt = (t - g[i - 1].2) as i64;
            dt.pow(2) < dx.pow(2) + dy.pow(2)
        };
        let f1 = if i == m {
            false
        } else {
            let dx = (x - g[i].0) as i64;
            let dy = (y - g[i].1) as i64;
            let dt = (t - g[i].2) as i64;
            dt.pow(2) < dx.pow(2) + dy.pow(2)
        };
        acc + (f0 || f1) as u32
    });
    writeln!(out, "{ans}").ok();
}

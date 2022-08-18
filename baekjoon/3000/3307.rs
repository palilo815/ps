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
    let n = sc.read::<usize>();
    let mut stack = Vec::with_capacity(n);
    for _ in 0..n {
        let x = sc.read::<f64>();
        let mut r = sc.read::<f64>();
        while let Some((px, pr)) = stack.last() {
            r = r.min((x - px) * (x - px) / 4.0 / pr);
            if r < *pr {
                break;
            }
            stack.pop();
        }
        stack.push((x, r));
        writeln!(out, "{:.4}", r).ok();
    }
}

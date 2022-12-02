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
    let mut acc = 0;
    for _ in 0..n {
        let x = sc.read::<i32>();
        acc = acc + if acc < 0 { x } else { -x };
    }
    acc = acc.abs();
    let ans = [100, 50, 20, 10, 5, 2, 1].into_iter().fold(0, |ans, w| {
        let cnt = acc / w;
        acc %= w;
        ans + cnt
    });
    writeln!(out, "{}", ans).ok();
}

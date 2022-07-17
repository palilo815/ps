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
    let m = sc.read::<usize>();
    for _ in 0..n {
        sc.read::<i32>();
        sc.read::<i32>();
    }
    let mut first = 0;
    let mut c = [0, 0];
    for _ in 0..m {
        sc.read::<i32>();
        sc.read::<i32>();
        match sc.read::<char>() {
            'R' => c[0] += 1,
            'B' => c[1] += 1,
            _ => first ^= 1,
        }
    }
    let win = first ^ (c[first] <= c[first ^ 1]) as usize;
    writeln!(out, "jhna{}917", ['h', 'n'][win]).ok();
}

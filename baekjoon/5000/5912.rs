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
    let k = sc.read::<usize>();
    let mut diff = vec![0; n + 1];
    for _ in 0..k {
        let l = sc.read::<usize>() - 1;
        let r = sc.read::<usize>();
        diff[l] += 1;
        diff[r] -= 1;
    }
    diff.pop();
    let mut acc = 0;
    for d in diff.iter_mut() {
        acc += *d;
        *d = acc;
    }
    diff.select_nth_unstable(n / 2);
    writeln!(out, "{}", diff[n / 2]).ok();
}

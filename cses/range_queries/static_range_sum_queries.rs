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
    let q = sc.read::<usize>();
    let mut pref = vec![0; n + 1];
    for i in 0..n {
        pref[i + 1] = pref[i] + sc.read::<u64>();
    }
    for _ in 0..q {
        let l = sc.read::<usize>() - 1;
        let r = sc.read::<usize>();
        writeln!(out, "{}", pref[r] - pref[l]).ok();
    }
}

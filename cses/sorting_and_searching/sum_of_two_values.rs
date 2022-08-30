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
    let x = sc.read::<u32>();
    let mut a = (0..n).map(|i| (sc.read::<u32>(), i)).collect::<Vec<_>>();
    a.sort_unstable_by(|lhs, rhs| lhs.0.cmp(&rhs.0));
    let (mut i, mut j) = (0, n - 1);
    while i != j {
        if a[i].0 + a[j].0 < x {
            i += 1;
        } else if a[i].0 + a[j].0 > x {
            j -= 1;
        } else {
            writeln!(out, "{} {}", a[i].1 + 1, a[j].1 + 1).ok();
            return;
        }
    }
    writeln!(out, "IMPOSSIBLE").ok();
}

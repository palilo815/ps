use std::io::Write;

pub struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    pub fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    pub fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let t = sc.read::<usize>();
    let mut a = [(0, 0); 100_000];
    for _ in 0..t {
        let n = sc.read::<usize>();
        let k = sc.read::<usize>();
        a.iter_mut().take(n).for_each(|x| x.0 = sc.read::<i32>());
        a.iter_mut().take(n).for_each(|x| x.1 = sc.read::<i32>());
        a[0..n].sort_unstable_by_key(|x| x.1 - x.0);
        let sz = (n - k + 1) / 2;
        let mut sum = a.iter().take(sz).fold(0, |acc, x| acc + x.0 as i64)
            + a.iter().take(n).skip(sz).fold(0, |acc, x| acc + x.1 as i64);
        let mut best = sum;
        for x in a.iter().take(n - sz).skip(sz) {
            sum += (x.0 - x.1) as i64;
            best = best.max(sum);
        }
        writeln!(out, "{}", best).ok();
    }
}

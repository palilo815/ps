use std::io::Write;

pub struct Scanner<'a> {
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
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.read::<usize>();
    let mut pref = vec![0; n + 1];
    for i in 0..n {
        let x = sc.read::<usize>();
        let y = sc.read::<u32>();
        pref[i + 1] = pref[i] + (pref[i] - pref[i - x] >= y) as u32;
    }
    writeln!(out, "{}", pref[n]).ok();
}


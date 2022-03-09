use std::io::Write;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn next<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let mut a = (0..n)
        .map(|_| (sc.next::<u32>(), sc.next::<u32>()))
        .collect::<Vec<_>>();
    a.sort_unstable_by(|lhs, rhs| rhs.0.cmp(&lhs.0));
    let mut name_pref = vec![0; n + 1];
    for i in 0..n {
        name_pref[i + 1] = name_pref[i] ^ a[i].1;
    }
    let prefs = (0..m)
        .map(|s| {
            let blocks = (n - s) / m;
            let mut pref = vec![0; blocks + 1];
            for i in 0..blocks {
                pref[i + 1] = pref[i] + (name_pref[s + i * m] ^ name_pref[s + (i + 1) * m]) as u64;
            }
            pref
        })
        .collect::<Vec<_>>();
    let q = sc.next::<usize>();
    for _ in 0..q {
        let a = sc.next::<usize>();
        let mut b = sc.next::<usize>();
        let offset = b / m;
        b %= m;
        writeln!(out, "{}", prefs[b][a + offset] - prefs[b][offset]).ok();
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

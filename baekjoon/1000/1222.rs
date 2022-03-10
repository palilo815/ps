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
    let mut cnt = [0; 2_000_001];
    (0..n).for_each(|_| cnt[sc.next::<usize>()] += 1);
    let mut ans = 0;
    for sz in 1..2_000_001 {
        let finalists = cnt.iter().step_by(sz).sum::<u32>() as usize;
        if finalists > 1 {
            ans = ans.max(sz * finalists);
        }
    }
    writeln!(out, "{}", ans).ok();
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

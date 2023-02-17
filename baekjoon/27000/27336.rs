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
    let mut kids = (0..4 * n)
        .map(|i| (i / n, sc.read::<u32>()))
        .collect::<Vec<_>>();
    kids.sort_unstable_by(|l, r| l.1.cmp(&r.1));
    let mut cnt = [0; 4];
    let mut r = 0;
    let mut ans = u32::MAX;
    for l in 0..4 * n {
        while r < 4 * n && cnt.iter().any(|&x| x == 0) {
            cnt[kids[r].0] += 1;
            r += 1;
        }
        if cnt.iter().any(|&x| x == 0) {
            break;
        }
        ans = ans.min(kids[r - 1].1 - kids[l].1);
        cnt[kids[l].0] -= 1;
    }
    writeln!(out, "{ans}").ok();
}

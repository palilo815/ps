use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let m = sc.read::<i32>();
    let mut segs = Vec::with_capacity(100_000);
    loop {
        let l = sc.read::<i32>();
        let r = sc.read::<i32>();
        if l == 0 && r == 0 {
            break;
        }
        if r > 0 {
            segs.push((l, r));
        }
    }
    segs.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    let mut lim = 0;
    let mut it = segs.into_iter().peekable();
    for cnt in 1.. {
        let mut nxt = i32::MIN;
        while let Some((_, r)) = it.next_if(|(l, _)| *l <= lim) {
            nxt = nxt.max(r);
        }
        if nxt == i32::MIN {
            writeln!(out, "0").ok();
            return;
        }
        lim = nxt;
        if lim >= m {
            writeln!(out, "{cnt}").ok();
            return;
        }
    }
}

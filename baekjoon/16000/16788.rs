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
    let n = sc.read::<usize>();
    let mut h = (1..=n).map(|i| (i, sc.read::<i32>())).collect::<Vec<_>>();
    h.sort_unstable_by(|l, r| r.1.cmp(&l.1));
    let mut land = vec![false; n + 2];
    let mut ans = 0;
    let mut acc = 0;
    let mut i = 0;
    while i != n && h[i].1 != 0 {
        let now = h[i].1;
        while i != n && h[i].1 == now {
            land[h[i].0] = true;
            match (land[h[i].0 - 1], land[h[i].0 + 1]) {
                (true, true) => acc -= 1,
                (false, false) => acc += 1,
                _ => {}
            }
            i += 1;
        }
        ans = ans.max(acc);
    }
    writeln!(out, "{ans}").ok();
}

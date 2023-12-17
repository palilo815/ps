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
    const N: usize = 1_000;
    let mut teams = [(0, 0, 0); N];
    loop {
        let n = sc.read::<usize>();
        let mut a = sc.read::<i32>();
        let mut b = sc.read::<i32>();
        if n == 0 {
            break;
        }
        let teams = &mut teams[..n];
        for x in teams.iter_mut() {
            x.0 = sc.read::<i32>();
            x.1 = sc.read::<i32>();
            x.2 = sc.read::<i32>();
        }
        teams.sort_unstable_by(|l, r| (l.1 - l.2).cmp(&(r.1 - r.2)));
        let mut ans = 0;
        for (k, _, db) in teams.iter() {
            ans += k * db;
            b -= k;
        }
        for (k, da, db) in teams.iter() {
            if da >= db && b >= 0 {
                break;
            }
            let swap = if da < db { a } else { -b }.min(*k);
            ans += swap * (da - db);
            a -= swap;
            b += swap;
        }
        writeln!(out, "{ans}").ok();
    }
}

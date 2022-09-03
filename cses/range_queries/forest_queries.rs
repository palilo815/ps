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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
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
    let m = sc.read::<usize>();
    let mut pref = vec![vec![0; n + 1]; n + 1];
    for i in 0..n {
        for (j, x) in sc.raw().chars().into_iter().enumerate() {
            pref[i + 1][j + 1] = -pref[i][j] + pref[i][j + 1] + pref[i + 1][j] + (x == '*') as i32;
        }
    }
    for _ in 0..m {
        let x0 = sc.read::<usize>() - 1;
        let y0 = sc.read::<usize>() - 1;
        let x1 = sc.read::<usize>();
        let y1 = sc.read::<usize>();
        writeln!(
            out,
            "{}",
            pref[x0][y0] - pref[x0][y1] - pref[x1][y0] + pref[x1][y1]
        )
        .ok();
    }
}

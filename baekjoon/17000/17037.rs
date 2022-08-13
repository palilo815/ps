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
    let k = sc.read::<i32>();
    let mut pref = [[0; 1002]; 1002];
    for _ in 0..n {
        let x0 = sc.read::<usize>();
        let y0 = sc.read::<usize>();
        let x1 = sc.read::<usize>();
        let y1 = sc.read::<usize>();
        pref[x0 + 1][y0 + 1] += 1;
        pref[x0 + 1][y1 + 1] -= 1;
        pref[x1 + 1][y0 + 1] -= 1;
        pref[x1 + 1][y1 + 1] += 1;
    }
    for i in 0..1000 {
        for j in 0..1000 {
            pref[i + 1][j + 1] += -pref[i][j] + pref[i][j + 1] + pref[i + 1][j];
        }
    }
    writeln!(
        out,
        "{}",
        pref.iter().flatten().filter(|&&x| x == k).count()
    )
    .ok();
}

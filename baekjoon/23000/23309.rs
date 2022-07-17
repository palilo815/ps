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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
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
    let mut link = vec![(0, 0); 1_000_001];
    {
        let a = sc.read_vec::<usize>(n);
        for i in 0..n {
            link[a[i]].0 = if i == 0 { a[n - 1] } else { a[i - 1] };
            link[a[i]].1 = if i == n - 1 { a[0] } else { a[i + 1] };
        }
    }
    for _ in 0..m {
        let s = sc.read_bytes();
        let i = sc.read::<usize>();
        if s[0] == b'B' {
            let j = sc.read::<usize>();
            let (u, v) = if s[1] == b'N' {
                writeln!(out, "{}", link[i].1).ok();
                (i, link[i].1)
            } else {
                writeln!(out, "{}", link[i].0).ok();
                (link[i].0, i)
            };
            link[u].1 = j;
            link[v].0 = j;
            link[j] = (u, v);
        } else {
            let i = if s[1] == b'N' { link[i].1 } else { link[i].0 };
            writeln!(out, "{}", i).ok();
            let (u, v) = link[i];
            link[u].1 = v;
            link[v].0 = u;
        }
    }
}

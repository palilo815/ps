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
    fn next<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn next_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.next()).collect()
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
    let n = sc.next::<usize>();
    let mut a = sc.next_vec::<u32>(n);
    let mut ans = 0;
    for i in 0..n - 1 {
        let b = sc.next::<u32>();
        if a[i] != b {
            a[i + 1] ^= a[i] ^ b;
            ans += 1;
        }
    }
    writeln!(
        out,
        "{}",
        if a[n - 1] == sc.next::<u32>() {
            ans
        } else {
            -1
        }
    )
    .ok();
}

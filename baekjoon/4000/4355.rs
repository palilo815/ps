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
    loop {
        let n = sc.read::<u32>();
        if n == 0 {
            break;
        }
        let mut x = n;
        let mut i = 2;
        let mut ans = n;
        while i * i <= x {
            if x % i == 0 {
                ans = ans / i * (i - 1);
                while x % i == 0 {
                    x /= i;
                }
            }
            i += 1;
        }
        if x != 1 {
            ans = ans / x * (x - 1);
        }
        writeln!(out, "{}", if n == 1 { 0 } else { ans }).ok();
    }
}

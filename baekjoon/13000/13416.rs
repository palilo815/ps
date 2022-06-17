use std::io::Write;

pub struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    pub fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    pub fn next<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
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
    let t = sc.next::<usize>();
    for _ in 0..t {
        let n = sc.next::<usize>();
        let mut res = 0;
        for _ in 0..n {
            let mut max = 0;
            max = max.max(sc.next::<i32>());
            max = max.max(sc.next::<i32>());
            max = max.max(sc.next::<i32>());
            res += max;
        }
        writeln!(out, "{}", res).ok();
    }
}

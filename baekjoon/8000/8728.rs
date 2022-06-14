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
    let n = sc.next::<usize>();
    let mut min_0 = usize::MAX;
    let mut min_1 = usize::MAX;
    let mut max_0 = 0;
    let mut max_1 = 0;
    for i in 0..n {
        let x = sc.next::<u32>();
        if x == 0 {
            if min_0 == usize::MAX {
                min_0 = i;
                max_0 = i;
            } else {
                max_0 = i;
            }
        } else {
            if min_1 == usize::MAX {
                min_1 = i;
                max_1 = i;
            } else {
                max_1 = i;
            }
        }
    }
    writeln!(out, "{}", (max_1 - min_0).max(max_0 - min_1)).ok();
}

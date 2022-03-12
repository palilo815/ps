use std::io::Write;

struct Scanner<'a> {
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
    let t = sc.next::<usize>();
    for _ in 0..t {
        let n = sc.next::<u32>();
        let a = sc.next_vec::<u32>(n as usize);
        let total = a.iter().sum::<u32>();
        for blocks in (0..n + 1).rev().filter(|&b| total % b == 0) {
            let b = total / blocks;
            let mut acc = 0;
            if a.iter().any(|&x| {
                acc += x;
                if acc == b {
                    acc = 0;
                }
                acc > b
            }) {
                continue;
            }
            writeln!(out, "{}", n - blocks).ok();
            break;
        }
    }
}

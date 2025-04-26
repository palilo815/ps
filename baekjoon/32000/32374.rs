use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut a = sc.read_vec::<u32>(n);
    let mut b = sc.read_vec::<u32>(n);
    let mut c = sc.read_vec::<u32>(k);
    a.sort_unstable();
    b.sort_unstable();
    c.sort_unstable();
    let mut bt = b.into_iter().rev().peekable();
    let mut ct = c.into_iter().rev();
    for gift in a.into_iter().rev() {
        while bt.peek().is_some_and(|&box_size| box_size >= gift) {
            if bt.next() != ct.next() {
                writeln!(bw, "{gift}").ok();
                return;
            }
        }
    }
}

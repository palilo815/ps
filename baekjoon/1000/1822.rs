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
    let m = sc.read::<usize>();
    let mut a = sc.read_vec::<u32>(n);
    let mut b = sc.read_vec::<u32>(m);
    a.sort_unstable();
    b.sort_unstable();
    let mut i = 0;
    a.retain(|&x| {
        while i != m && b[i] < x {
            i += 1;
        }
        i == m || b[i] != x
    });
    writeln!(bw, "{}", a.len()).ok();
    for x in a {
        write!(bw, "{x} ").ok();
    }
}

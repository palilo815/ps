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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut rchild = vec![0; n];
    for _ in 0..n {
        let i = sc.read::<usize>() - 1;
        sc.raw();
        rchild[i] = sc.read::<i32>() - 1;
    }
    let mut ans = 2 * (n - 1);
    let mut u = 0;
    while rchild[u as usize] != -2 {
        u = rchild[u as usize];
        ans -= 1;
    }
    writeln!(bw, "{ans}").ok();
}

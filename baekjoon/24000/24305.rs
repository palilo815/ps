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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<i32>();
    let mut stack = Vec::with_capacity(n as usize + 1);
    stack.push((0, 0));
    for i in 1..=n {
        let x = sc.read::<i32>();
        while stack.last().unwrap().1 >= x {
            stack.pop();
        }
        write!(bw, "{} ", stack.last().unwrap().0).ok();
        stack.push((i, x));
    }
}

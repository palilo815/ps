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
    let mut stack = vec![];
    let ans = (0..n)
        .filter(|_| {
            stack.clear();
            for c in sc.raw().bytes() {
                if stack.last().is_some_and(|&x| x == c) {
                    stack.pop();
                } else {
                    stack.push(c);
                }
            }
            stack.is_empty()
        })
        .count();
    writeln!(bw, "{ans}").ok();
}

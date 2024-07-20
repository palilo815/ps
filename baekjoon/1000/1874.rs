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
    let n = sc.read::<usize>();
    let mut i = 1;
    let mut stack = Vec::with_capacity(n);
    let mut ans = Vec::with_capacity(2 * n);
    for _ in 0..n {
        let x = sc.read::<i32>();
        while i <= x {
            ans.push(b'+');
            ans.push(b'\n');
            stack.push(i);
            i += 1;
        }
        if stack.last().is_some_and(|&top| top == x) {
            stack.pop();
            ans.push(b'-');
            ans.push(b'\n');
        }
    }
    if stack.is_empty() {
        writeln!(bw, "{}", String::from_utf8(ans).unwrap()).ok();
    } else {
        writeln!(bw, "NO").ok();
    }
}

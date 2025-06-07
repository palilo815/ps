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
    let mut stack = Vec::with_capacity(n);
    let mut target = 1;
    for _ in 0..n {
        while stack.last().is_some_and(|&x| x == target) {
            stack.pop();
            target += 1;
        }
        let x = sc.read::<i32>();
        if x == target {
            target += 1;
        } else {
            stack.push(x);
        }
    }
    let expected = (target..).take(stack.len());
    let ans = stack.into_iter().rev().eq(expected);
    writeln!(bw, "{}", if ans { "Nice" } else { "Sad" }).ok();
}

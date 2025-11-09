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
    let mut stack = vec![];
    let n = sc.read::<usize>();
    for _ in 0..n {
        match sc.read::<char>() {
            '1' => stack.push(sc.read::<i32>()),
            '2' => writeln!(bw, "{}", stack.pop().unwrap_or(-1)).unwrap(),
            '3' => writeln!(bw, "{}", stack.len()).unwrap(),
            '4' => writeln!(bw, "{}", stack.is_empty() as usize).unwrap(),
            _ => writeln!(bw, "{}", stack.last().unwrap_or(&-1)).unwrap(),
        }
    }
}

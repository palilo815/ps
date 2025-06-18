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
    let mut dq = std::collections::VecDeque::new();
    for _ in 0..n {
        match sc.raw() {
            "push_front" => dq.push_front(sc.read::<i32>()),
            "push_back" => dq.push_back(sc.read::<i32>()),
            "pop_front" => writeln!(bw, "{}", dq.pop_front().unwrap_or(-1)).unwrap(),
            "pop_back" => writeln!(bw, "{}", dq.pop_back().unwrap_or(-1)).unwrap(),
            "size" => writeln!(bw, "{}", dq.len()).unwrap(),
            "empty" => writeln!(bw, "{}", dq.is_empty() as usize).unwrap(),
            "front" => writeln!(bw, "{}", dq.front().unwrap_or(&-1)).unwrap(),
            "back" => writeln!(bw, "{}", dq.back().unwrap_or(&-1)).unwrap(),
            _ => unreachable!(),
        }
    }
}

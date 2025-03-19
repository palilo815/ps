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
    fn read_chars(&mut self) -> Vec<char> {
        self.it.next().unwrap().chars().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut s = sc.read_chars();
    let count_l = s.iter().filter(|&&c| c == '(').count();
    let count_r = s.iter().filter(|&&c| c == ')').count();
    s.iter_mut().filter(|c| **c == 'G').take(n / 2 - count_l).for_each(|c| *c = '(');
    s.iter_mut().filter(|c| **c == 'G').take(n / 2 - count_r).for_each(|c| *c = ')');
    writeln!(bw, "{}", s.into_iter().collect::<String>()).ok();
}

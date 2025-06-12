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
    const N: usize = 50;
    let mut a = [0; N];
    for t in 1.. {
        let n = sc.read::<usize>();
        if n == 0 {
            break;
        }
        let a = &mut a[..n];
        a.fill_with(|| sc.read::<i32>());
        let avg = a.iter().sum::<i32>() / n as i32;
        let ans = a.iter().map(|&x| 0.max(x - avg)).sum::<i32>();
        writeln!(bw, "Set #{t}\nThe minimum number of moves is {ans}.\n").ok();
    }
}

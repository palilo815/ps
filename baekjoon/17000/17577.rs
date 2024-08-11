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
    let mut score = [0; 1000];
    loop {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        if n == 0 && m == 0 {
            break;
        }
        let score = &mut score[..n];
        score.fill(0);
        for _ in 0..m {
            score.iter_mut().for_each(|x| *x += sc.read::<i32>());
        }
        writeln!(bw, "{}", score.iter().max().unwrap()).ok();
    }
}

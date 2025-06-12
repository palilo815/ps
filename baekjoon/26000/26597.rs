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

#[derive(PartialEq)]
enum Answer {
    GotIt(usize),
    Paradox(usize),
    Hmm,
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let mut l = -1_000_000_000_000_000_000_i64;
    let mut r = 1_000_000_000_000_000_000_i64;
    let mut ans = Answer::Hmm;
    let n = sc.read::<usize>();
    for i in 1..=n {
        let x = sc.read::<i64>();
        if sc.read::<char>() == '^' {
            l = l.max(x + 1);
        } else {
            r = r.min(x - 1);
        }
        if l == r && ans == Answer::Hmm {
            ans = Answer::GotIt(i);
        } else if l > r {
            ans = Answer::Paradox(i);
            break;
        }
    }
    match ans {
        Answer::GotIt(i) => writeln!(bw, "I got it!\n{i}").unwrap(),
        Answer::Paradox(i) => writeln!(bw, "Paradox!\n{i}").unwrap(),
        Answer::Hmm => writeln!(bw, "Hmm...").unwrap(),
    }
}

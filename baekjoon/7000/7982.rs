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
    let mut ans = Vec::with_capacity(n + 1);
    ans.push(1);
    let mut mx = 1;
    for i in 1..=n {
        mx = mx.max(sc.read::<usize>());
        if mx == i {
            ans.push(i + 1);
        }
    }
    writeln!(bw, "{}", ans.len() - 1).ok();
    for w in ans.windows(2) {
        write!(bw, "{}", w[1] - w[0]).ok();
        for x in w[0]..w[1] {
            write!(bw, " {x}").ok();
        }
        writeln!(bw).ok();
    }
}

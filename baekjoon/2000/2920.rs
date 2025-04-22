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
    const ASC: [i32; 8] = [1, 2, 3, 4, 5, 6, 7, 8];
    const DES: [i32; 8] = [8, 7, 6, 5, 4, 3, 2, 1];
    let mut a = [0; 8];
    a.fill_with(|| sc.read::<i32>());
    let ans = match a {
        ASC => "ascending",
        DES => "descending",
        _ => "mixed",
    };
    writeln!(bw, "{ans}").ok();
}

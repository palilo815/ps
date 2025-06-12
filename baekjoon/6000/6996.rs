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
    for _ in 0..n {
        let a = sc.read::<String>();
        let b = sc.read::<String>();
        let mut count = [0; 26];
        a.bytes().for_each(|x| count[(x - b'a') as usize] += 1);
        b.bytes().for_each(|x| count[(x - b'a') as usize] -= 1);
        writeln!(
            bw,
            "{a} & {b} are {}anagrams.",
            if count == [0; 26] { "" } else { "NOT " }
        )
        .ok();
    }
}

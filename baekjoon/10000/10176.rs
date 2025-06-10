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
    let t = sc.read::<usize>();
    for _ in 0..t {
        let s = sc.raw();
        let mut check = [false; 26];
        for c in s.bytes() {
            match c {
                b'a'..=b'z' => check[(c - b'a') as usize] = true,
                b'A'..=b'Z' => check[(c - b'A') as usize] = true,
                _ => {}
            }
        }
        let yes = check.iter().eq(check.iter().rev());
        writeln!(bw, "{}", if yes { "Yes" } else { "No" }).ok();
    }
}

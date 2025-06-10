use std::io::*;

struct Scanner {
    it: std::str::Split<'static, char>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split('\n') }
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
    for _ in 0..n {
        let mut check = [false; 26];
        let s = sc.raw();
        for c in s.bytes().filter(|c| c.is_ascii_alphabetic()) {
            check[(c.to_ascii_lowercase() - b'a') as usize] = true;
        }
        if check.iter().all(|&x| x) {
            writeln!(bw, "pangram").ok();
        } else {
            let missing = check
                .into_iter()
                .enumerate()
                .filter_map(|(i, c)| if c { None } else { Some(i as u8 + b'a') })
                .collect::<Vec<_>>();
            writeln!(bw, "missing {}", String::from_utf8(missing).unwrap()).ok();
        }
    }
}

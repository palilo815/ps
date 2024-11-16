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
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let _ = sc.read::<usize>();
    let mut m = sc.read::<i32>();
    let mut s = sc.read_bytes();
    let mut cnt = [0; 26];
    for c in s.iter().map(|&c| (c - b'a') as usize) {
        cnt[c] += 1;
    }
    for c in cnt.iter_mut() {
        *c = m.min(*c);
        m -= *c;
    }
    s.retain(|&c| {
        let c = (c - b'a') as usize;
        if cnt[c] == 0 {
            true
        } else {
            cnt[c] -= 1;
            false
        }
    });
    writeln!(bw, "{}", String::from_utf8(s).unwrap()).ok();
}

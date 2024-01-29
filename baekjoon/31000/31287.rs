use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let k = n.min(sc.read::<usize>());
    let s = sc.read_bytes();
    let mut x = 0;
    let mut y = 0;
    for c in s.into_iter().cycle().take(n * k) {
        match c {
            b'U' => x -= 1,
            b'D' => x += 1,
            b'L' => y -= 1,
            _ => y += 1,
        }
        if x == 0 && y == 0 {
            writeln!(out, "YES").ok();
            return;
        }
    }
    writeln!(out, "NO").ok();
}

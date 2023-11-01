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
    let t = sc.read::<usize>();
    for _ in 0..t {
        let mut s = sc.read_bytes();
        let m = (0..s.len()).find(|&len| s.iter().skip(len).eq(s.iter().skip(len).rev())).unwrap();
        s.extend(s.clone().iter().take(m).rev());
        writeln!(out, "{}", String::from_utf8(s).unwrap()).ok();
    }
}

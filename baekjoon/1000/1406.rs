use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
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
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let mut l = sc.read_bytes();
    let mut r = vec![];
    let n = sc.read::<usize>();
    for _ in 0..n {
        match sc.read::<char>() {
            'L' => {
                if let Some(c) = l.pop() {
                    r.push(c);
                }
            }
            'D' => {
                if let Some(c) = r.pop() {
                    l.push(c);
                }
            }
            'B' => {
                l.pop();
            }
            _ => {
                l.push(sc.read::<char>() as u8);
            }
        }
    }
    r.reverse();
    write!(bw, "{}", String::from_utf8(l).unwrap()).ok();
    write!(bw, "{}", String::from_utf8(r).unwrap()).ok();
}

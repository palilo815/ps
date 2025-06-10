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
    let mut dict = [0; 28];
    for (dict, alpha) in dict.iter_mut().zip(b'A'..=b'Z') {
        *dict = alpha;
    }
    dict[26] = b'_';
    dict[27] = b'.';
    loop {
        let n = sc.read::<usize>();
        if n == 0 {
            break;
        }
        let mut s = sc.read_bytes();
        s.reverse();
        s.iter_mut().for_each(|c| {
            *c = match *c {
                b'_' => dict[(n + 26) % 28],
                b'.' => dict[(n + 27) % 28],
                _ => dict[((*c - b'A') as usize + n) % 28],
            }
        });
        writeln!(bw, "{}", String::from_utf8(s).unwrap()).ok();
    }
}

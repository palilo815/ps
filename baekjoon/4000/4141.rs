use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
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
    const PAD: [u8; 26] = [
        2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9,
    ];
    let t = sc.read::<usize>();
    let mut v = vec![];
    for _ in 0..t {
        v.clear();
        for x in sc.read_bytes() {
            v.push(PAD[(x - if x.is_ascii_lowercase() { b'a' } else { b'A' }) as usize]);
        }
        let ans = if v.iter().eq(v.iter().rev()) {
            "YES"
        } else {
            "NO"
        };
        writeln!(out, "{ans}").ok();
    }
}

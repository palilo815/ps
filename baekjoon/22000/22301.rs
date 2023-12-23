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
        let mut l = 0;
        let mut r = s.len() - 1;
        let mut less = false;
        while l < r {
            if s[l] < s[r] {
                less = true;
            } else if s[l] > s[r] {
                less = false;
            }
            s[r] = s[l];
            l += 1;
            r -= 1;
        }
        if less {
            if l == r {
                s[l] += 1;
            } else {
                l -= 1;
                r += 1;
                s[l] += 1;
                s[r] += 1;
            }
        }
        while s[l] > b'9' {
            s[l] = b'0';
            s[r] = b'0';
            l -= 1;
            r += 1;
            s[l] += 1;
            s[r] += 1;
        }
        writeln!(out, "{}", String::from_utf8(s).unwrap()).ok();
    }
}

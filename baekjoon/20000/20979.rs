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
    let n = sc.read::<usize>();
    let mut i = sc.read::<usize>();
    let s = sc.read_bytes();
    let mut l = i;
    let mut r = i;
    while l != 0 && s[l - 1] == b'.' {
        l -= 1;
    }
    while r != n + 1 && s[r - 1] == b'.' {
        r += 1;
    }
    let mut acc = 0;
    let mut turn = false;
    loop {
        if l == 0 && r == n + 1 {
            break;
        }
        match turn {
            false => {
                acc += r - i;
                i = r;
                if r != n + 1 {
                    r += 1;
                    while r != n + 1 && s[r - 1] == b'.' {
                        r += 1;
                    }
                }
            }
            true => {
                acc += i - l;
                i = l;
                if l != 0 {
                    l -= 1;
                    while l != 0 && s[l - 1] == b'.' {
                        l -= 1;
                    }
                }
            }
        }
        turn ^= true;
    }
    writeln!(out, "{acc}").ok();
}

use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a String) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    const SIZE: usize = 1 << 21;
    let mut bit = [0; SIZE | 1];
    let q = sc.next::<usize>();
    for _ in 0..q {
        let op = sc.next::<char>();
        let x = sc.next::<u32>();
        if op == '1' {
            let mut i = (x + 1) as usize;
            while i <= SIZE {
                bit[i] += 1;
                i += i & i.wrapping_neg();
            }
        } else {
            let mut x = x;
            let mut i = 0;
            let mut len = SIZE >> 1;
            while len != 0 {
                if bit[i | len] < x {
                    i |= len;
                    x -= bit[i];
                } else {
                    bit[i | len] -= 1;
                }
                len >>= 1;
            }
            writeln!(out, "{}", i).ok();
        }
    }
}

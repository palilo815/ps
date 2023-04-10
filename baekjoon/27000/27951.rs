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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let mut a = sc.read_vec::<u8>(n);
    let mut u = sc.read::<usize>();
    let mut d = sc.read::<usize>();
    let cnt_u = a.iter().filter(|&&x| x == 1).count();
    let cnt_d = a.iter().filter(|&&x| x == 2).count();
    if cnt_u > u || cnt_d > d {
        writeln!(out, "NO").ok();
        return;
    }
    u -= cnt_u;
    d -= cnt_d;
    writeln!(out, "YES").ok();
    for x in a.iter_mut() {
        *x = match *x {
            1 => b'U',
            2 => b'D',
            _ => {
                if u > 0 {
                    u -= 1;
                    b'U'
                } else {
                    d -= 1;
                    b'D'
                }
            }
        };
    }
    writeln!(out, "{}", String::from_utf8(a).unwrap()).ok();
}

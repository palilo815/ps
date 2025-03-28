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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let s = sc.read_vec::<char>(n);
    let mut l = 0;
    let mut r = n;
    for i in 1..=n {
        let mut flag = false;
        let mut ll = l;
        let mut rr = r - 1;
        while ll < rr {
            if s[ll] != s[rr] {
                flag = s[ll] < s[rr];
                break;
            }
            ll += 1;
            rr -= 1;
        }
        let c = if flag {
            l += 1;
            s[l - 1]
        } else {
            r -= 1;
            s[r]
        };
        write!(bw, "{c}").ok();
        if i % 80 == 0 {
            writeln!(bw).ok();
        }
    }
}

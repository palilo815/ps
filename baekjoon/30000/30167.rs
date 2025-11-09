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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let l = sc.read::<usize>();
    let r = sc.read::<usize>();
    let ans = (l..=r)
        .find(|&x| {
            let mut check = [false; 10];
            let mut x = x;
            while x != 0 {
                if check[x % 10] {
                    return false;
                }
                check[x % 10] = true;
                x /= 10;
            }
            true
        })
        .unwrap_or(usize::MAX);
    writeln!(bw, "{}", ans as isize).ok();
}

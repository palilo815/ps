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
    let a = sc.read_vec::<u32>(n);
    let mut blue = vec![0; n];
    for i in (1..n).rev() {
        blue[i - 1] = a[i].max(blue[i]);
    }
    let mut red = 0;
    let mut s = 0;
    for i in 0..n - 1 {
        red = red.max(a[i]);
        if red > blue[i] {
            s += 1;
        } else if red < blue[i] {
            s -= 1;
        }
    }
    writeln!(
        out,
        "{}",
        if s > 0 {
            'R'
        } else if s < 0 {
            'B'
        } else {
            'X'
        }
    )
    .ok();
}

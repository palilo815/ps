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
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let a = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>())).collect::<Vec<_>>();
    let mut acc = 0.0;
    for (i, (x1, y1)) in a.iter().enumerate() {
        for (x2, y2) in a.iter().take(i) {
            let dx = x1 - x2;
            let dy = y1 - y2;
            acc += f64::sqrt((dx * dx + dy * dy).into());
        }
    }
    writeln!(out, "{:.8}", acc * 2.0 / n as f64).ok();
}

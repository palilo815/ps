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
    let mut a = [0; 9];
    a.fill_with(|| sc.read::<i32>());
    let target = a.iter().sum::<i32>() - 100;
    for i in 0..9 {
        for j in 0..i {
            if a[i] + a[j] == target {
                a[i] = -1;
                a[j] = -1;
            }
        }
    }
    for x in a.into_iter().filter(|&x| x != -1) {
        writeln!(bw, "{x}").ok();
    }
}

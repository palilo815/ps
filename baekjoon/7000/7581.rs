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
    let mut a = [0; 4];
    loop {
        a.fill_with(|| sc.read::<u32>());
        if a.iter().sum::<u32>() == 0 {
            break;
        }
        if a[3] == 0 {
            a[3] = a.iter().take(3).product::<u32>();
        } else {
            let miss = a[3] / a.iter().take(3).filter(|&&x| x != 0).product::<u32>();
            *a.iter_mut().find(|x| **x == 0).unwrap() = miss;
        }
        for x in a {
            write!(bw, "{x} ").ok();
        }
        writeln!(bw).ok();
    }
}

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
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut a = (1..=n).map(|i| (sc.read::<u32>(), sc.read::<u32>(), i)).collect::<Vec<_>>();
    a.sort_unstable();
    let mut b = (0..m).map(|i| (sc.read::<u32>(), i)).collect::<Vec<_>>();
    b.sort_unstable();
    let mut ans = vec![0; m];
    let mut it = a.into_iter();
    for (x, i) in b.into_iter() {
        for (y, z, j) in it.by_ref() {
            if x == y || x == z {
                ans[i] = j;
                break;
            }
        }
    }
    if ans.contains(&0) {
        writeln!(bw, "impossible").ok();
    } else {
        for x in ans {
            writeln!(bw, "{x}").ok();
        }
    }
}

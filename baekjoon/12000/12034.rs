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
    const N: usize = 100;
    let mut p = [0; 2 * N];
    let t = sc.read::<usize>();
    for t in 1..=t {
        let n = sc.read::<usize>();
        let p = &mut p[..2 * n];
        p.fill_with(|| sc.read::<u32>());
        write!(bw, "Case #{t}:").ok();
        let mut j = 1;
        for i in 0..p.len() {
            if p[i] == 0 {
                continue;
            }
            write!(bw, " {}", p[i]).ok();
            let q = p[i] / 3 * 4;
            while p[j] < q {
                j += 1;
            }
            p[j] = 0;
        }
        writeln!(bw).ok();
    }
}

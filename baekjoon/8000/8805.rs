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
    const N: usize = 1_000_000;
    let mut a = vec![0; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let k = sc.read::<usize>();
        if n == 1 {
            writeln!(bw, "{k}").ok();
            continue;
        }
        let a = &mut a[..n];
        let cycle = ((k - 1) / (2 * n - 2)) as u32;
        let rem = (k - 1) % (2 * n - 2);
        a[0] = cycle;
        a[1..n - 1].fill(cycle * 2);
        a[n - 1] = cycle;
        for i in (1..n).chain((0..n - 1).rev()).take(rem) {
            a[i] += 1;
        }
        a[0] += 1;
        for x in a {
            write!(bw, "{x} ").ok();
        }
        writeln!(bw).ok();
    }
}

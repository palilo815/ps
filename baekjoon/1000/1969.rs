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
    fn raw(&mut self) -> &str {
        self.it.next().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const ACGT: [char; 4] = ['A', 'C', 'G', 'T'];
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut cnt = vec![[0; 4]; m];
    for _ in 0..n {
        let s = sc.raw();
        for (c, cnt) in s.bytes().zip(cnt.iter_mut()) {
            match c {
                b'A' => cnt[0] += 1,
                b'C' => cnt[1] += 1,
                b'G' => cnt[2] += 1,
                b'T' => cnt[3] += 1,
                _ => unreachable!(),
            }
        }
    }
    let mut dist = 0;
    let ans = cnt
        .into_iter()
        .map(|cnt| {
            let mx = *cnt.iter().max().unwrap();
            let i = cnt.into_iter().position(|x| x == mx).unwrap();
            dist += n - mx;
            ACGT[i]
        })
        .collect::<String>();
    writeln!(bw, "{ans}\n{dist}").ok();
}

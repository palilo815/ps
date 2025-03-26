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
    fn ignore(&mut self, n: usize) {
        for _ in 0..n {
            self.it.next();
        }
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const M: usize = 1_000_000;
    let n = sc.read::<usize>();
    let a = (0..n).map(|_| sc.read::<u32>() - 1).collect::<Vec<_>>();
    let mut pref = vec![0; M + 1];
    for x in a.iter() {
        pref[*x as usize] += 1;
    }
    for i in 0..M {
        pref[i + 1] += pref[i];
    }
    let mut indice = vec![0; n];
    for (i, x) in a.into_iter().enumerate().rev() {
        pref[x as usize] -= 1;
        indice[pref[x as usize]] = i;
    }
    let q = sc.read::<usize>();
    for _ in 0..q {
        let m = sc.read::<usize>();
        let mut ans = "TAK";
        let mut i = 0;
        for j in 0..m {
            let x = sc.read::<usize>() - 1;
            let indice = &indice[pref[x]..pref[x + 1]];
            let lower_bound = indice.partition_point(|&y| y < i);
            if lower_bound == indice.len() {
                ans = "NIE";
                sc.ignore(m - j - 1);
                break;
            }
            i = indice[lower_bound] + 1;
        }
        writeln!(bw, "{ans}").ok();
    }
}

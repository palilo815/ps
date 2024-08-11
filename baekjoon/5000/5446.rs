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
    fn read_array<const N: usize>(&mut self) -> [u8; N] {
        let s = self.it.next().unwrap();
        let mut a = [0; N];
        a[..s.len()].copy_from_slice(s.as_bytes());
        a
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 1000;
    const M: usize = 20;
    let mut a = [[0; M]; N];
    let mut b = [[0; M]; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        a.iter_mut().for_each(|x| *x = sc.read_array());
        let n = sc.read::<usize>();
        let b = &mut b[..n];
        b.iter_mut().for_each(|x| *x = sc.read_array());
        if b.is_empty() {
            writeln!(bw, "1").ok();
            continue;
        }
        a.sort_unstable();
        b.sort_unstable();
        let mut i = 0;
        let mut ans = 0;
        while i != a.len() {
            let key = a[i];
            let len = (1..)
                .find(|&len| b.binary_search_by(|x| x.iter().take(len).cmp(key.iter().take(len))).is_err())
                .unwrap();
            i += 1;
            while i != a.len() && key.iter().take(len).eq(a[i].iter().take(len)) {
                i += 1;
            }
            ans += 1;
        }
        writeln!(bw, "{ans}").ok();
    }
}

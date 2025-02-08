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
    let mut ord = [0; 1000];
    let mut ans = [[0; 10]; 1000];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let ord = &mut ord[..n];
        let ans = &mut ans[..n];
        let map = (0..n).map(|i| (sc.read_array::<10>(), i)).collect::<std::collections::HashMap<_, _>>();
        for ord in ord.iter_mut() {
            *ord = *map.get(&sc.read_array()).unwrap();
        }
        for &ord in ord.iter() {
            ans[ord] = sc.read_array();
        }
        for (i, b) in ans.iter().enumerate() {
            let end = b.iter().position(|x| *x == 0).unwrap_or(10);
            write!(bw, "{}", std::str::from_utf8(&b[..end]).unwrap()).ok();
            write!(bw, "{}", if i + 1 == n { '\n' } else { ' ' }).ok();
        }
    }
}

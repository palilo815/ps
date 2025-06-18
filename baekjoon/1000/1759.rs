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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn f(res: &mut Vec<char>, a: &[char], st: usize) {
    if res.len() == res.capacity() {
        let vowel = res.iter().filter(|x| ['a', 'e', 'i', 'o', 'u'].contains(x)).count();
        if vowel != 0 && res.len() - vowel > 1 {
            println!("{}", res.iter().collect::<String>());
        }
        return;
    }
    for i in st..a.len() {
        res.push(a[i]);
        f(res, a, i + 1);
        res.pop();
    }
}

fn main() {
    let mut sc = Scanner::new();
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut a = sc.read_vec::<char>(m);
    a.sort_unstable();
    let mut buf = Vec::with_capacity(n);
    f(&mut buf, &a, 0);
}

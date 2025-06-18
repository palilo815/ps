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

struct Cipher {
    num: i32,
    count: i32,
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let _ = sc.read::<usize>();
    let mut a = Vec::<Cipher>::with_capacity(n);
    for _ in 0..n {
        let x = sc.read::<i32>();
        if let Some(it) = a.iter_mut().find(|c| c.num == x) {
            it.count += 1;
        } else {
            a.push(Cipher { num: x, count: 1 });
        }
    }
    a.sort_by(|l, r| r.count.cmp(&l.count));
    for Cipher { num, count } in a {
        for _ in 0..count {
            write!(bw, "{num} ").ok();
        }
    }
}

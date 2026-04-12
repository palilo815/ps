use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = Vec::new();
        stdin().lock().read_to_end(&mut buf).ok();
        let s = unsafe { std::str::from_utf8_unchecked(Box::leak(buf.into_boxed_slice())) };
        Self { it: s.split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

const V: [(i32, i32, i32); 6] = [(1, 0, 0), (0, 1, 0), (0, 0, 1), (-1, 0, 0), (0, -1, 0), (0, 0, -1)];

fn f(n: usize, dir: usize, vec: &mut Vec<(i32, i32, i32)>) -> u64 {
    let pos = *vec.last().unwrap();
    if vec[..vec.len() - 1].contains(&pos) {
        return if vec.len() == n + 2 { 1 } else { 0 };
    }
    if vec.len() == n + 2 {
        return 0;
    }
    let d1 = (dir + 5) % 6;
    let d2 = (dir + 1) % 6;
    vec.push((pos.0 + V[d1].0, pos.1 + V[d1].1, pos.2 + V[d1].2));
    let r1 = f(n, d1, vec);
    vec.pop();
    vec.push((pos.0 + V[d2].0, pos.1 + V[d2].1, pos.2 + V[d2].2));
    let r2 = f(n, d2, vec);
    vec.pop();
    r1 + r2
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut vec = Vec::with_capacity(n + 1);
    vec.push((0, 0, 0));
    vec.push(V[0]);
    let ans = f(n, 0, &mut vec);
    writeln!(bw, "{ans}").ok();
}

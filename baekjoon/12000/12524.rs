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

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 1_000;
    let mut f = [0; N];
    let mut visited = [false; N];
    let mut res = [0; N];
    let t = sc.read::<usize>();
    for t in 1..=t {
        let n = sc.read::<usize>();
        let f = &mut f[..n];
        let visited = &mut visited[..n];
        let res = &mut res[..n];
        f.fill_with(|| sc.read::<usize>() - 1);
        res.fill(0);
        for i in 0..n {
            visited.fill(false);
            let mut i = i;
            while !visited[i] {
                visited[i] = true;
                res[i] += 1;
                i = f[i];
            }
        }
        writeln!(bw, "Case #{t}:").ok();
        for x in res {
            writeln!(bw, "{x}").ok();
        }
    }
}

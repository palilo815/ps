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
    const N: usize = 1000;
    let mut a = [0; N];
    let mut visited = [false; N];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let a = &mut a[..n];
        let visited = &mut visited[..n];
        a.fill_with(|| sc.read::<usize>() - 1);
        visited.fill(false);
        let mut ans = 0;
        for i in 0..n {
            if visited[i] {
                continue;
            }
            ans += 1;
            let mut j = i;
            while !visited[j] {
                visited[j] = true;
                j = a[j];
            }
        }
        writeln!(bw, "{ans}").ok();
    }
}

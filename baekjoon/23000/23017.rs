use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a String) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let t = sc.next::<u32>();
    for tc in 1..=t {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();
        let mut grid = (0..n).map(|_| sc.next_bytes()).collect::<Vec<_>>();
        let mut adj = vec![[usize::MAX; 4]; n * m];
        for i in 0..n {
            let mut s = 0;
            loop {
                while s != m && grid[i][s] == b'#' {
                    s += 1;
                }
                if s == m {
                    break;
                }
                let mut t = s;
                while t != m && grid[i][t] != b'#' {
                    t += 1;
                }
                for j in 0..(t - s) {
                    adj[i * m + s + j][0] = i * m + t - 1 - j;
                    adj[i * m + t - 1 - j][1] = i * m + s + j;
                }
                s = t;
            }
        }
        for j in 0..m {
            let mut s = 0;
            loop {
                while s != n && grid[s][j] == b'#' {
                    s += 1;
                }
                if s == n {
                    break;
                }
                let mut t = s;
                while t != n && grid[t][j] != b'#' {
                    t += 1;
                }
                for i in 0..(t - s) {
                    adj[(s + i) * m + j][2] = (t - 1 - i) * m + j;
                    adj[(t - 1 - i) * m + j][3] = (s + i) * m + j;
                }
                s = t;
            }
        }
        let empty = grid.iter().flatten().filter(|&&x| x == b'.').count();
        let mut stk = vec![];
        for (i, &x) in grid.iter().flatten().enumerate() {
            if x != b'.' && x != b'#' {
                stk.push(i);
            }
        }
        while let Some(u) = stk.pop() {
            for &v in adj[u].iter() {
                if v != usize::MAX && grid[v / m][v % m] == b'.' {
                    grid[v / m][v % m] = grid[u / m][u % m];
                    stk.push(v);
                }
            }
        }
        writeln!(
            out,
            "Case #{}: {}",
            tc,
            empty - grid.iter().flatten().filter(|&&x| x == b'.').count()
        )
        .ok();
        for x in grid.into_iter() {
            writeln!(out, "{}", String::from_utf8(x).unwrap()).ok();
        }
    }
}

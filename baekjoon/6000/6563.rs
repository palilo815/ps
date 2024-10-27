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
    let mut adj = [[0; 200]; 200];
    loop {
        let n = sc.read::<usize>();
        if n == 0 {
            break;
        }
        adj.fill([0; 200]);
        loop {
            let u = sc.read::<usize>() - 1;
            let v = sc.read::<usize>() - 1;
            if u == usize::MAX {
                break;
            }
            adj[u][v] = sc.raw().bytes().fold(0, |acc, x| acc | 1 << (x - b'a'));
        }
        for k in 0..n {
            for i in 0..n {
                for j in 0..n {
                    adj[i][j] |= adj[i][k] & adj[k][j];
                }
            }
        }
        loop {
            let u = sc.read::<usize>() - 1;
            let v = sc.read::<usize>() - 1;
            if u == usize::MAX {
                break;
            }
            if adj[u][v] == 0 {
                writeln!(bw, "-").ok();
            } else {
                for i in 0..26 {
                    if adj[u][v] >> i & 1 == 1 {
                        write!(bw, "{}", (b'a' + i) as char).ok();
                    }
                }
                writeln!(bw).ok();
            }
        }
        writeln!(bw).ok();
    }
}

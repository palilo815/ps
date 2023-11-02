use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let mut adj = [[0; 26]; 26];
    let mut prev = sc.read_bytes();
    for _ in 1..n {
        let curr = sc.read_bytes();
        if let Some((&u, &v)) = prev.iter().zip(curr.iter()).find(|x| x.0 != x.1) {
            adj[(u - b'a') as usize][(v - b'a') as usize] = 1;
        } else if prev.len() > curr.len() {
            writeln!(out, "impossible").ok();
            return;
        }
        prev = curr;
    }
    let mut indeg = [0; 26];
    for row in adj.iter() {
        for v in 0..26 {
            indeg[v] += row[v];
        }
    }
    let mut topo = (0..26).filter(|&i| indeg[i] == 0).collect::<Vec<_>>();
    for i in 0..26 {
        if i == topo.len() {
            writeln!(out, "impossible").ok();
            return;
        }
        let u = topo[i];
        for v in 0..26 {
            if adj[u][v] == 1 {
                indeg[v] -= 1;
                if indeg[v] == 0 {
                    topo.push(v);
                }
            }
        }
    }
    let s = topo.into_iter().map(|x| x as u8 + b'a').collect::<Vec<_>>();
    writeln!(out, "{}", String::from_utf8(s).unwrap()).ok();
}

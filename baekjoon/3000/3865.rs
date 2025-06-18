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

fn dfs(g: &[Vec<usize>], visited: &mut [bool], u: usize) -> usize {
    if std::mem::replace(&mut visited[u], true) {
        0
    } else if g[u].is_empty() {
        1
    } else {
        g[u].iter().fold(0, |acc, &v| acc + dfs(g, visited, v))
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const N: usize = 1_100;
    let mut visited = [false; N];
    let mut adj = vec![vec![]; N];
    let mut map = std::collections::HashMap::new();
    let to_array = |s: &str| {
        let mut arr = [0; 15];
        arr[..s.len()].copy_from_slice(s.as_bytes());
        arr
    };
    loop {
        let n = sc.read::<usize>();
        if n == 0 {
            break;
        }
        visited.fill(false);
        adj.iter_mut().for_each(|v| v.clear());
        map.clear();
        for _ in 0..n {
            let s = sc.raw();
            let (group, members) = s.split_once(':').unwrap();
            let len = map.len();
            let group = *map.entry(to_array(group)).or_insert(len);
            adj[group].extend(members.split_terminator([',', '.']).map(|s| {
                let len = map.len();
                *map.entry(to_array(s)).or_insert(len)
            }));
        }
        writeln!(bw, "{}", dfs(&adj, &mut visited, 0)).ok();
    }
}

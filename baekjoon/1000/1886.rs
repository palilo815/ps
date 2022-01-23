macro_rules! input {
    (source = $s:expr, $($r:tt)*) => {
        let mut iter = $s.split_whitespace();
        input_inner!{iter, $($r)*}
    };
    ($($r:tt)*) => {
        let s = {
            use std::io::Read;
            let mut s = String::new();
            std::io::stdin().read_to_string(&mut s).unwrap();
            s
        };
        let mut iter = s.split_whitespace();
        input_inner!{iter, $($r)*}
    };
}

macro_rules! input_inner {
    ($iter:expr) => {};
    ($iter:expr, ) => {};
    ($iter:expr, $var:ident : $t:tt $($r:tt)*) => {
        let $var = read_value!($iter, $t);
        input_inner!{$iter $($r)*}
    };
}

macro_rules! read_value {
    ($iter:expr, ( $($t:tt),* )) => {
        ( $(read_value!($iter, $t)),* )
    };
    ($iter:expr, [ $t:tt ; $len:expr ]) => {
        (0..$len).map(|_| read_value!($iter, $t)).collect::<Vec<_>>()
    };
    ($iter:expr, chars) => {
        read_value!($iter, String).chars().collect::<Vec<char>>()
    };
    ($iter:expr, bytes) => {
        read_value!($iter, String).bytes().collect::<Vec<u8>>()
    };
    ($iter:expr, usize1) => {
        read_value!($iter, usize) - 1
    };
    ($iter:expr, $t:ty) => {
        $iter.next().unwrap().parse::<$t>().expect("Parse error")
    };
}

struct BipartiteMatching {
    n: usize,
    m: usize,
    adj: Vec<Vec<usize>>,
}

impl BipartiteMatching {
    fn new(n: usize, m: usize) -> Self {
        Self {
            n,
            m,
            adj: vec![vec![]; n],
        }
    }
    fn add_edge(&mut self, u: usize, v: usize) {
        assert!(u < self.n && v < self.m);
        self.adj[u].push(v);
    }
    fn matching(&mut self, dist: Vec<Vec<u32>>) -> u32 {
        let mut visited = vec![false; self.n];
        let mut mat = vec![usize::MAX; self.n];
        let mut rmat = vec![usize::MAX; self.m];
        for t in 1.. {
            for (u, d) in dist.iter().enumerate() {
                for (v, x) in d.iter().enumerate() {
                    if *x <= t {
                        self.add_edge(v, (t - 1) as usize * dist.len() + u);
                    }
                }
            }
            let mut update = true;
            while update {
                visited.fill(false);
                update = false;
                for u in 0..self.n {
                    update |=
                        mat[u] == usize::MAX && self.dfs(&mut visited, &mut mat, &mut rmat, u);
                }
            }
            if mat.iter().all(|x| *x != usize::MAX) {
                return t;
            }
        }
        unreachable!();
    }
    fn dfs(&self, visited: &mut [bool], mat: &mut [usize], rmat: &mut [usize], u: usize) -> bool {
        visited[u] = true;
        for &v in self.adj[u].iter() {
            if rmat[v] == usize::MAX || (!visited[rmat[v]] && self.dfs(visited, mat, rmat, rmat[v]))
            {
                mat[u] = v;
                rmat[v] = u;
                return true;
            }
        }
        false
    }
}

fn main() {
    use std::io::Write;
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    input! {
        n: usize,
        m: usize,
        grid: [bytes; n],
    }
    let mut src = vec![];
    let mut dest = vec![];
    for i in 0..n {
        for j in 0..m {
            if grid[i][j] == b'.' {
                src.push((i, j));
            } else if grid[i][j] == b'D' {
                dest.push((i, j));
            }
        }
    }
    if dest.is_empty() {
        writeln!(out, "impossible").ok();
        return;
    }
    let dist = {
        const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
        let mut q = std::collections::VecDeque::new();
        let mut dist = vec![vec![0; m]; n];
        dest.iter()
            .map(|s| {
                dist.iter_mut().for_each(|x| x.fill(u32::MAX));
                dist[s.0][s.1] = 0;
                q.push_back(*s);
                while let Some((x, y)) = q.pop_front() {
                    for &(dx, dy) in MOVE.iter() {
                        let xx = x + dx;
                        let yy = y + dy;
                        if xx == usize::MAX || xx == n || yy == usize::MAX || yy == m {
                            continue;
                        }
                        if grid[xx][yy] == b'.' && dist[xx][yy] == u32::MAX {
                            dist[xx][yy] = dist[x][y] + 1;
                            q.push_back((xx, yy));
                        }
                    }
                }
                src.iter().map(|x| dist[x.0][x.1]).collect::<Vec<_>>()
            })
            .collect::<Vec<_>>()
    };
    if (0..src.len()).any(|i| dist.iter().all(|d| d[i] == u32::MAX)) {
        writeln!(out, "impossible").ok();
        return;
    }
    let mut matcher = BipartiteMatching::new(src.len(), (n - 2) * (m - 2) * dest.len());
    writeln!(out, "{}", matcher.matching(dist)).ok();
}

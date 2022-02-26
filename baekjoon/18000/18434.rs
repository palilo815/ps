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

trait ChMinMax {
    fn chmin(&mut self, x: Self) -> bool;
    fn chmax(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChMinMax for T {
    fn chmin(&mut self, x: Self) -> bool {
        *self > x && {
            *self = x;
            true
        }
    }
    fn chmax(&mut self, x: Self) -> bool {
        *self < x && {
            *self = x;
            true
        }
    }
}

fn main() {
    use std::io::Write;
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    input! {
        n: usize,
        m: usize,
        edges: [(usize1, usize1, u32, u32); m],
    }
    let mut edges = edges;
    const INF: u32 = 0x5f5f5f5f;
    let mut d = vec![vec![INF; n]; n];
    (0..n).for_each(|i| d[i][i] = 0);
    for e in edges.iter() {
        d[e.0][e.1].chmin(e.2);
    }
    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                let new_d = d[i][k] + d[k][j];
                d[i][j].chmin(new_d);
            }
        }
    }
    let mut dist = vec![0; n];
    let mut visited = vec![false; n];
    let mut dijk =
        |adj: &[Vec<usize>], e: &[(usize, usize, u32, u32)], s: usize, t: usize| -> u32 {
            visited.fill(false);
            dist.fill(INF);
            dist[s] = 0;
            loop {
                let u = (0..n)
                    .filter(|&i| !visited[i])
                    .min_by_key(|&i| dist[i])
                    .unwrap();
                visited[u] = true;
                if u == t || dist[u] == INF {
                    return dist[u];
                }
                for edge in adj[u]
                    .iter()
                    .map(|&i| &e[i])
                    .filter(|edge| !visited[edge.1])
                {
                    let d = dist[u] + edge.2;
                    dist[edge.1].chmin(d);
                }
            }
        };
    let mut adj = vec![vec![]; n];
    for (i, e) in edges.iter().enumerate() {
        adj[e.0].push(i);
    }
    let (d1, d2) = (d[0][n - 1], d[n - 1][0]);
    let mut ans = d1 + d2;
    for i in 0..m {
        let (u, v, w1, w2) = edges[i];
        let d1 = d1.min(d[0][v] + w1 + d[u][n - 1]);
        let d2 = d2.min(d[n - 1][v] + w1 + d[u][0]);
        if d1 + d2 + w2 < ans {
            let eid = adj[u].iter().position(|&x| x == i).unwrap();
            adj[u].swap_remove(eid);
            adj[v].push(i);
            edges[i].0 = v;
            edges[i].1 = u;
            let d1 = dijk(&adj, &edges, 0, n - 1);
            let d2 = dijk(&adj, &edges, n - 1, 0);
            ans.chmin(d1 + d2 + w2);
            edges[i].0 = u;
            edges[i].1 = v;
            adj[v].pop();
            adj[u].push(i);
        }
    }
    if ans < INF {
        writeln!(out, "{}", ans).ok();
    } else {
        writeln!(out, "-1").ok();
    }
}

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

use std::io::Write;

fn main() {
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    input! {
        n: usize,
        m: usize,
        s: usize1,
        k: usize,
        edges: [(usize1, usize1); m],
    }
    let mut adj = vec![vec![]; n];
    for &(u, v) in edges.iter() {
        adj[u].push(v);
        adj[v].push(u);
    }
    if adj[s].is_empty() {
        write!(out, "-1").ok();
        return;
    }
    const INF: i32 = 0x3f3f3f3f;
    let mut dist = vec![[INF; 2]; n];
    dist[s][0] = 0;
    let mut q = std::collections::VecDeque::new();
    q.push_back((s, 0));
    while let Some((u, cur)) = q.pop_front() {
        let nxt = cur ^ 1;
        for &v in adj[u].iter() {
            if dist[v][nxt] == INF {
                dist[v][nxt] = dist[u][cur] + 1;
                q.push_back((v, nxt));
            }
        }
    }
    let ans = (0..n)
        .map(|x| {
            if dist[x][k & 1] <= k as i32 {
                x + 1
            } else {
                usize::MAX
            }
        })
        .filter(|&x| x != usize::MAX)
        .collect::<Vec<_>>();
    for &x in ans.iter() {
        write!(out, "{} ", x).ok();
    }
}

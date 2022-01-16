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

fn main() {
    use std::io::Write;
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    input! {
        n: usize,
        e: [(usize1, usize1); n - 1],
    }
    let mut adj = vec![vec![]; n];
    for &(u, v) in e.iter() {
        adj[u].push((1, v));
        adj[v].push((-1, u));
    }
    let mut par = vec![usize::MAX; n];
    let mut stk = vec![0];
    let mut dp = vec![0; n];
    while let Some(u) = stk.pop() {
        if let Some(p) = adj[u].iter().position(|&(_, x)| x == par[u]) {
            adj[u].swap_remove(p);
        }
        for &(w, v) in adj[u].iter() {
            par[v] = u;
            dp[v] = dp[u] + w;
            stk.push(v);
        }
    }
    let mut i = (0..n).min_by_key(|&x| dp[x]).unwrap();
    let mut step_p = usize::MAX;
    while i != usize::MAX {
        let p = std::mem::replace(&mut par[i], step_p);
        step_p = std::mem::replace(&mut i, p);
    }
    for &(u, v) in e.iter() {
        write!(out, "{}", (par[u] == v) as i32).ok();
    }
}

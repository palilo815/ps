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

struct DisjointSet {
    p: Vec<i32>,
}

#[allow(dead_code)]
impl DisjointSet {
    fn new(n: usize) -> Self {
        Self { p: vec![-1; n] }
    }
    fn clear(&mut self) {
        self.p.fill(-1);
    }
    fn find(&mut self, u: usize) -> usize {
        if self.p[u] < 0 {
            u
        } else {
            let rt = self.find(self.p[u] as usize);
            self.p[u] = rt as i32;
            rt
        }
    }
    fn unite(&mut self, u: usize, v: usize) -> bool {
        let mut u = self.find(u);
        let mut v = self.find(v);
        if u == v {
            return false;
        }
        if self.p[u] > self.p[v] {
            std::mem::swap(&mut u, &mut v);
        }
        self.p[u] += self.p[v];
        self.p[v] = u as i32;
        true
    }
    fn same(&mut self, u: usize, v: usize) -> bool {
        self.find(u) == self.find(v)
    }
    fn size_of(&mut self, u: usize) -> usize {
        let root = self.find(u);
        (-self.p[root]) as usize
    }
    fn num_components(&self) -> usize {
        self.p.iter().filter(|x| x.is_negative()).count()
    }
    fn iter_roots(&self) -> impl Iterator<Item = usize> + '_ {
        self.p
            .iter()
            .enumerate()
            .filter_map(|(i, x)| match x.is_negative() {
                true => Some(i),
                false => None,
            })
    }
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
        k: usize,
        edges: [(usize1, usize1, u32); m],
        new_edges: [(usize1, usize1); k],
        p: [u32; n],
    }
    let mut dsu = DisjointSet::new(n);
    for &(u, v) in new_edges.iter() {
        dsu.unite(u, v);
    }
    let mut edges = edges;
    edges.sort_unstable_by_key(|x| x.2);
    let (must_in_mst, mut rival_edges): (Vec<(usize, usize, u32)>, Vec<(usize, usize, u32)>) =
        edges.into_iter().partition(|e| dsu.unite(e.0, e.1));
    dsu.clear();
    for e in must_in_mst {
        dsu.unite(e.0, e.1);
    }
    let mut component_id = vec![0; n];
    for (i, x) in dsu.iter_roots().enumerate() {
        component_id[x] = i;
    }
    for x in 0..n {
        component_id[x] = component_id[dsu.find(x)];
    }
    let root = component_id[0];
    let mut new_edges = new_edges;
    new_edges.iter_mut().for_each(|e| {
        e.0 = component_id[e.0];
        e.1 = component_id[e.1];
    });
    rival_edges.retain(|e| dsu.unite(e.0, e.1));
    rival_edges.iter_mut().for_each(|e| {
        e.0 = component_id[e.0];
        e.1 = component_id[e.1];
    });
    let n = component_id.iter().max().unwrap() + 1;
    let mut component_size = vec![0; n];
    for (i, x) in p.into_iter().enumerate() {
        component_size[component_id[i]] += x as u64;
    }
    let mut adj = vec![vec![]; n];
    let mut dsu = DisjointSet::new(n);
    let mut stk = Vec::with_capacity(n);
    let mut dep = vec![0; n];
    let mut par = vec![usize::MAX; n];
    let mut dfs_order = vec![0; n];
    let mut dp = vec![0; n];
    let mut mn = vec![0; n];
    let mut ans = 0;
    for mask in 1..(1 << k) {
        dsu.clear();
        adj.iter_mut().for_each(|x| x.clear());
        if new_edges.iter().enumerate().any(|(i, e)| {
            mask >> i & 1 == 1 && {
                adj[e.0].push(e.1);
                adj[e.1].push(e.0);
                !dsu.unite(e.0, e.1)
            }
        }) {
            continue;
        }
        rival_edges.iter().for_each(|e| {
            if dsu.unite(e.0, e.1) {
                adj[e.0].push(e.1);
                adj[e.1].push(e.0);
            }
        });
        dep.fill(-1);
        dep[root] = 0;
        stk.push(root);
        for it in dfs_order.iter_mut() {
            let u = stk.pop().unwrap();
            *it = u;
            if let Some(p) = adj[u].iter().position(|x| *x == par[u]) {
                adj[u].swap_remove(p);
            }
            for &v in adj[u].iter() {
                if dep[v] == -1 {
                    dep[v] = dep[u] + 1;
                    par[v] = u;
                    stk.push(v);
                }
            }
        }
        dp.copy_from_slice(&component_size);
        dfs_order.iter().rev().for_each(|&u| {
            dp[u] += adj[u].iter().fold(0, |acc, &v| acc + dp[v]);
        });
        mn.fill(u32::MAX);
        rival_edges.iter().for_each(|e| {
            let mut u = e.0;
            let mut v = e.1;
            while u != v {
                if dep[u] < dep[v] {
                    std::mem::swap(&mut u, &mut v);
                }
                mn[u].chmin(e.2);
                u = par[u];
            }
        });
        let res = new_edges
            .iter()
            .enumerate()
            .filter(|(i, _)| mask >> i & 1 == 1)
            .fold(0, |acc, (_, e)| {
                let child = if dep[e.0] > dep[e.1] { e.0 } else { e.1 };
                acc + dp[child] * mn[child] as u64
            });
        ans.chmax(res);
    }
    writeln!(out, "{}", ans).ok();
}

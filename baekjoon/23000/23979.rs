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

use std::io::Write;

pub trait Monoid: std::clone::Clone + std::marker::Copy {
    fn id() -> Self;
    fn op(lhs: &Self, rhs: &Self) -> Self;
}

mod segment_tree {
    use crate::Monoid;

    pub struct SegmentTree<T: Monoid> {
        n: usize,
        tree: Vec<T>,
    }

    #[allow(dead_code)]
    impl<T: Monoid> SegmentTree<T> {
        pub fn new(n: usize) -> Self {
            Self {
                n,
                tree: vec![T::id(); n << 1],
            }
        }
        pub fn build_with(data: Vec<T>) -> Self {
            let n = data.len();
            let mut a = vec![T::id(); n << 1];
            a[n..].copy_from_slice(&data);
            for i in (1..n).rev() {
                a[i] = T::op(&a[i << 1], &a[i << 1 | 1]);
            }
            Self { n, tree: a }
        }
        pub fn get(&self, i: usize) -> T {
            self.tree[i + self.n]
        }
        pub fn set(&mut self, mut i: usize, x: T) {
            i += self.n;
            self.tree[i] = x;
            while i != 1 {
                i >>= 1;
                self.tree[i] = T::op(&self.tree[i << 1], &self.tree[i << 1 | 1]);
            }
        }
        pub fn update(&mut self, mut i: usize, x: T) {
            i += self.n;
            self.tree[i] = T::op(&self.tree[i], &x);
            while i != 1 {
                i >>= 1;
                self.tree[i] = T::op(&self.tree[i << 1], &self.tree[i << 1 | 1]);
            }
        }
        pub fn product(&self, mut l: usize, mut r: usize) -> T {
            let mut ret = T::id();
            l += self.n;
            r += self.n;
            while l != r {
                if l & 1 == 1 {
                    ret = T::op(&ret, &self.tree[l]);
                    l += 1;
                }
                if r & 1 == 1 {
                    r -= 1;
                    ret = T::op(&self.tree[r], &ret);
                }
                l >>= 1;
                r >>= 1;
            }
            ret
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
    let n = sc.next::<usize>();
    let q = sc.next::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<u32>();
        adj[u].push((w, v));
        adj[v].push((w, u));
    }
    let mut stk = Vec::with_capacity(n);
    let mut par = vec![0; n];
    let mut cost = vec![0; n];
    let mut rev_dfn = vec![0; n];
    stk.push(0);
    for u in rev_dfn.iter_mut().rev() {
        *u = stk.pop().unwrap();
        if let Some(parent_edge) = adj[*u].iter().position(|&x| x.1 == par[*u]) {
            adj[*u].swap_remove(parent_edge);
        }
        for &(w, v) in adj[*u].iter() {
            par[v] = *u;
            cost[v] = w;
            stk.push(v);
        }
    }
    let mut sz = vec![0; n];
    for &u in rev_dfn.iter() {
        sz[u] = adj[u].iter().map(|&x| sz[x.1]).sum::<u32>() + 1;
        if let Some((heavy, &(_, _))) = adj[u].iter().enumerate().max_by_key(|&(_, x)| sz[x.1]) {
            let last = adj[u].len() - 1;
            adj[u].swap(heavy, last);
        }
    }
    let mut top = vec![0; n];
    let mut in_time = vec![0; n];
    let mut dist = vec![0; n];
    stk.push(0);
    for t in 0..n {
        let u = stk.pop().unwrap();
        in_time[u] = t;
        for &(w, v) in adj[u].iter() {
            top[v] = v;
            dist[v] = dist[u] + w as u64;
            stk.push(v);
        }
        if !adj[u].is_empty() {
            top[*stk.last().unwrap()] = top[u];
        }
    }
    #[derive(Clone, Copy)]
    struct Node {
        w: u32,
        i: usize,
    }
    impl Monoid for Node {
        fn id() -> Self {
            Self { w: 0, i: 0 }
        }
        fn op(lhs: &Self, rhs: &Self) -> Self {
            if lhs.w > rhs.w {
                *lhs
            } else {
                *rhs
            }
        }
    }
    let mut leaves = vec![Node { w: 0, i: 0 }; n];
    for i in 0..n {
        leaves[in_time[i]].w = cost[i];
        leaves[in_time[i]].i = i;
    }
    let seg = segment_tree::SegmentTree::build_with(leaves);
    let get_lca = |mut u: usize, mut v: usize| {
        while top[u] != top[v] {
            if sz[top[u]] < sz[top[v]] {
                u = par[top[u]];
            } else {
                v = par[top[v]];
            }
        }
        if in_time[u] < in_time[v] {
            u
        } else {
            v
        }
    };
    let get_dist = |u: usize, v: usize| {
        let lca = get_lca(u, v);
        dist[u] + dist[v] - 2 * dist[lca]
    };
    let query = |mut u: usize, mut v: usize| {
        let mut ret = Node::id();
        while top[u] != top[v] {
            if sz[top[u]] > sz[top[v]] {
                std::mem::swap(&mut u, &mut v);
            }
            ret = Node::op(&ret, &seg.product(in_time[top[u]], in_time[u] + 1));
            u = par[top[u]];
        }
        if in_time[u] > in_time[v] {
            std::mem::swap(&mut u, &mut v);
        }
        Node::op(&ret, &seg.product(in_time[u] + 1, in_time[v] + 1))
    };
    for _ in 0..q {
        let mut u = sc.next::<usize>() - 1;
        let mut v = sc.next::<usize>() - 1;
        let w = sc.next::<u64>();
        let a = sc.next::<usize>() - 1;
        let b = sc.next::<usize>() - 1;
        let x = query(u, v).i;
        let a_in_sub = in_time[x] <= in_time[a] && in_time[a] < in_time[x] + sz[x] as usize;
        let b_in_sub = in_time[x] <= in_time[b] && in_time[b] < in_time[x] + sz[x] as usize;
        if a_in_sub ^ b_in_sub {
            let u_in_sub = in_time[x] <= in_time[u] && in_time[u] < in_time[x] + sz[x] as usize;
            if a_in_sub ^ u_in_sub {
                std::mem::swap(&mut u, &mut v);
            }
            writeln!(out, "{}", get_dist(a, u) + get_dist(b, v) + w).ok();
        } else {
            writeln!(out, "{}", get_dist(a, b)).ok();
        }
    }
}

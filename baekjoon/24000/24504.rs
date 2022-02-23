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

struct SegmentTree<T, F> {
    size: usize,
    tree: Vec<T>,
    id: T,
    op: F,
}

impl<T, F> std::ops::Index<usize> for SegmentTree<T, F> {
    type Output = T;
    fn index(&self, i: usize) -> &T {
        &self.tree[i + self.size]
    }
}
impl<T, F> std::ops::IndexMut<usize> for SegmentTree<T, F> {
    fn index_mut(&mut self, i: usize) -> &mut T {
        &mut self.tree[i + self.size]
    }
}

#[allow(dead_code)]
impl<T, F> SegmentTree<T, F>
where
    T: Clone + std::marker::Copy,
    F: Fn(&T, &T) -> T,
{
    fn new(size: usize, id: T, op: F) -> Self {
        SegmentTree {
            size,
            tree: vec![id; size << 1],
            id,
            op,
        }
    }
    fn from(leaves: Vec<T>, id: T, op: F) -> Self {
        let size = leaves.len();
        let mut tree = leaves;
        tree.extend_from_within(..);
        for i in (1..size).rev() {
            tree[i] = op(&tree[i << 1], &tree[i << 1 | 1]);
        }
        tree[0] = id;
        Self { size, tree, id, op }
    }
    fn build(&mut self) {
        for i in (1..self.size).rev() {
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    fn clear(&mut self) {
        self.tree[1..].fill(self.id);
    }
    fn set(&mut self, mut i: usize, x: T) {
        assert!(i < self.size);
        i += self.size;
        self.tree[i] = x;
        while i != 1 {
            i >>= 1;
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    fn update(&mut self, mut i: usize, x: T) {
        assert!(i < self.size);
        i += self.size;
        self.tree[i] = (self.op)(&self.tree[i], &x);
        while i != 1 {
            i >>= 1;
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    fn product(&self, mut l: usize, mut r: usize) -> T {
        assert!(l <= r && r <= self.size);
        let mut ret = self.id;
        l += self.size;
        r += self.size;
        while l != r {
            if l & 1 == 1 {
                ret = (self.op)(&ret, &self.tree[l]);
                l += 1;
            }
            if r & 1 == 1 {
                r -= 1;
                ret = (self.op)(&self.tree[r], &ret);
            }
            l >>= 1;
            r >>= 1;
        }
        ret
    }
    fn all_product(&self) -> T {
        self.tree[1]
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
        edges: [(usize1, usize1); m],
    }
    if m & 1 == 0 {
        writeln!(out, "{}", 0).ok();
        return;
    }
    let mut adj = vec![vec![]; n];
    for e in edges.iter() {
        adj[e.0].push(e.1);
        adj[e.1].push(e.0);
    }
    let (par, tin, tout) = {
        let mut par = vec![usize::MAX; n];
        let mut tin = vec![-1; n];
        let mut tout = vec![0; n];
        let mut stk = Vec::with_capacity(n);
        stk.push(0);
        par[0] -= 1;
        let mut t = 0;
        for _ in 0..(n << 1) {
            let u = stk.pop().unwrap();
            if tin[u] != -1 {
                tout[u] = t;
                continue;
            }
            tin[u] = t;
            t += 1;
            stk.push(u);
            for &v in adj[u].iter() {
                if par[v] == usize::MAX {
                    par[v] = u;
                    stk.push(v);
                }
            }
        }
        (par, tin, tout)
    };
    let dp = {
        let mut ids = (0..n).collect::<Vec<_>>();
        ids.sort_unstable_by_key(|&x| tin[x]);
        let mut dp = adj.iter().map(|x| x.len() as u32).collect::<Vec<_>>();
        for &u in ids.iter().skip(1).rev() {
            dp[par[u]] += dp[u];
        }
        dp
    };
    const INF: i32 = 0x3f3f3f3f;
    let mut seg = SegmentTree::new(n, (INF, !INF), |lhs, rhs| {
        (lhs.0.min(rhs.0), lhs.1.max(rhs.1))
    });
    for i in 0..n {
        seg[i] = (i as i32, i as i32);
    }
    let mut ans = vec![false; m];
    for (e, ok) in edges.iter().zip(ans.iter_mut()) {
        if par[e.0] != e.1 && par[e.1] != e.0 {
            *ok = true;
            seg[tin[e.0] as usize].0.chmin(tin[e.1]);
            seg[tin[e.0] as usize].1.chmax(tin[e.1]);
            seg[tin[e.1] as usize].0.chmin(tin[e.0]);
            seg[tin[e.1] as usize].1.chmax(tin[e.0]);
        }
    }
    seg.build();
    for (e, ok) in edges.iter().zip(ans.iter_mut()) {
        if *ok {
            continue;
        }
        let u = if par[e.0] == e.1 { e.0 } else { e.1 };
        let (mn, mx) = seg.product(tin[u] as usize, tout[u] as usize);
        *ok = mn < tin[u] || tout[u] <= mx || (dp[u] >> 1 & 1 == 0);
    }
    writeln!(out, "{}", ans.iter().filter(|x| **x).count()).ok();
    for (i, _) in ans.into_iter().enumerate().filter(|(_, x)| *x) {
        write!(out, "{} ", i + 1).ok();
    }
}

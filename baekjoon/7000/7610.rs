use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
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

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

pub struct BinaryIndexedTree<T> {
    size: usize,
    tree: Vec<T>,
    id: T,
}

#[allow(dead_code)]
impl<T> BinaryIndexedTree<T>
where
    T: std::clone::Clone
        + std::cmp::PartialOrd
        + std::marker::Copy
        + std::ops::AddAssign
        + std::ops::SubAssign
        + std::ops::Sub<Output = T>,
{
    pub fn new(size: usize, id: T) -> Self {
        BinaryIndexedTree {
            size,
            tree: vec![id; size + 1],
            id,
        }
    }
    pub fn build(&mut self) {
        for i in 1..self.size {
            let val = self.tree[i];
            let idx = i + (i & i.wrapping_neg());
            if idx <= self.size {
                self.tree[idx] += val;
            }
        }
    }
    pub fn clear(&mut self) {
        self.tree[1..].fill(self.id);
    }
    pub fn get(&self, i: usize) -> T {
        assert!(i < self.size);
        if i & 1 == 0 {
            self.product(i, i + 1)
        } else {
            self.tree[i + 1]
        }
    }
    pub fn fake_update(&mut self, i: usize, x: T) {
        if i != self.size {
            self.tree[i + 1] += x;
        }
    }
    pub fn update(&mut self, mut i: usize, x: T) {
        assert!(i <= self.size);
        i += 1;
        while i <= self.size {
            self.tree[i] += x;
            i += i & i.wrapping_neg();
        }
    }
    pub fn prefix(&self, mut i: usize) -> T {
        assert!(i <= self.size);
        let mut ret = self.id;
        while i != 0 {
            ret += self.tree[i];
            i &= i - 1;
        }
        ret
    }
    pub fn product(&self, l: usize, r: usize) -> T {
        assert!(l <= r);
        self.prefix(r) - self.prefix(l)
    }
    pub fn lower_bound(&self, mut k: T) -> usize {
        let mut i = 0;
        let mut pw = 1 << 20;
        while pw != 0 {
            if (i | pw) <= self.size && self.tree[i | pw] < k {
                i |= pw;
                k -= self.tree[i];
            }
            pw >>= 1;
        }
        i
    }
    pub fn upper_bound(&self, mut k: T) -> usize {
        let mut i = 0;
        let mut pw = 1 << 20;
        while pw != 0 {
            if (i | pw) <= self.size && self.tree[i | pw] <= k {
                i |= pw;
                k -= self.tree[i];
            }
            pw >>= 1;
        }
        i
    }
}

fn binary_lifting(data: Vec<usize>) -> Vec<Vec<usize>> {
    assert!(!data.is_empty());
    let mut par = vec![
        vec![];
        (8 * std::mem::size_of::<usize>())
            - (data.len() - 1).leading_zeros() as usize
    ];
    par[0] = data;
    for i in 1..par.len() {
        par[i] = par[i - 1]
            .iter()
            .map(|&x| {
                if x == usize::MAX {
                    usize::MAX
                } else {
                    par[i - 1][x]
                }
            })
            .collect::<Vec<_>>();
    }
    par
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let q = sc.next::<usize>();
    let mut edges = (1..n)
        .map(|_| (sc.next::<usize>() - 1, sc.next::<usize>() - 1))
        .collect::<Vec<_>>();
    let mut adj = vec![vec![]; n];
    for e in edges.iter() {
        adj[e.0].push(e.1);
        adj[e.1].push(e.0);
    }
    let (tin, tout, par) = {
        let mut tin = vec![usize::MAX; n];
        let mut tout = vec![0; n];
        let mut par = vec![usize::MAX; n];
        let mut stk = Vec::with_capacity(n);
        stk.push(0);
        let mut t = 0;
        for _ in 0..(n << 1) {
            let u = stk.pop().unwrap();
            if tin[u] != usize::MAX {
                tout[u] = t;
                continue;
            }
            tin[u] = t;
            t += 1;
            stk.push(u);
            if let Some(p) = adj[u].iter().position(|&x| x == par[u]) {
                adj[u].swap_remove(p);
            }
            for &v in adj[u].iter() {
                par[v] = u;
                stk.push(v);
            }
        }
        (tin, tout, par)
    };
    edges.iter_mut().filter(|e| par[e.1] == e.0).for_each(|e| {
        std::mem::swap(&mut e.0, &mut e.1);
    });
    let par = binary_lifting(par);
    let mut bit = BinaryIndexedTree::new(n, 0);
    tin.iter().zip(tout.iter()).for_each(|(&i, &o)| {
        bit.fake_update(i, 1);
        bit.fake_update(o, -1);
    });
    bit.build();
    let get_root = |bit: &BinaryIndexedTree<i32>, u: usize| -> usize {
        let groups = bit.prefix(tin[u] + 1);
        let mut r = u;
        for p in par.iter().rev() {
            if p[r] != usize::MAX && bit.prefix(tin[p[r]] + 1) == groups {
                r = p[r];
            }
        }
        r
    };
    let mut now = vec![1; n];
    let mut prv = vec![0; n];
    let mut con = vec![false; m];
    for _ in 0..m {
        let i = sc.next::<usize>() - 1;
        let child = edges[i].0;
        let root = get_root(&bit, edges[i].1);
        con[i] ^= true;
        if con[i] {
            now[root] += now[child] - prv[child];
            bit.update(tin[child], -1);
            bit.update(tout[child], 1);
        } else {
            now[child] = now[root];
            prv[child] = now[root];
            bit.update(tin[child], 1);
            bit.update(tout[child], -1);
        }
    }
    for _ in 0..q {
        writeln!(out, "{}", now[get_root(&bit, sc.next::<usize>() - 1)]).ok();
    }
}

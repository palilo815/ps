use std::io::Write;

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

struct LazySeg<T, U, F1, F2, F3> {
    size: usize,
    height: usize,
    tree: Vec<T>,
    lazy: Vec<U>,
    id: T,
    off: U,
    op: F1,
    mapping: F2,
    composition: F3,
}

impl<T, U, F1, F2, F3> std::ops::Index<usize> for LazySeg<T, U, F1, F2, F3> {
    type Output = T;
    fn index(&self, i: usize) -> &T {
        &self.tree[i | self.size]
    }
}
impl<T, U, F1, F2, F3> std::ops::IndexMut<usize> for LazySeg<T, U, F1, F2, F3> {
    fn index_mut(&mut self, i: usize) -> &mut T {
        &mut self.tree[i | self.size]
    }
}

impl<T, U, F1, F2, F3> LazySeg<T, U, F1, F2, F3>
where
    T: Clone + std::marker::Copy,
    U: Clone + std::marker::Copy + std::cmp::PartialEq,
    F1: Fn(&T, &T) -> T,
    F2: Fn(&mut T, &U),
    F3: Fn(&mut U, &U),
{
    fn new(size: usize, id: T, off: U, op: F1, mapping: F2, composition: F3) -> Self {
        let size = size.next_power_of_two();
        let height = size.trailing_zeros() as usize + 1;
        LazySeg {
            size,
            height,
            tree: vec![id; size << 1],
            lazy: vec![off; size],
            id,
            off,
            op,
            mapping,
            composition,
        }
    }
    fn build(&mut self) {
        (1..self.size).rev().for_each(|i| self._pull(i));
    }
    fn apply(&mut self, mut l: usize, mut r: usize, f: U) {
        assert!(l <= r && r <= self.size);
        if l == r {
            return;
        }
        l |= self.size;
        r += self.size;
        for i in (1..self.height).rev() {
            if (l >> i << i) != l {
                self._push(l >> i);
            }
            if (r >> i << i) != r {
                self._push((r - 1) >> i);
            }
        }
        {
            let mut l = l;
            let mut r = r;
            while l != r {
                if l & 1 == 1 {
                    self._all_apply(l, f);
                    l += 1;
                }
                if r & 1 == 1 {
                    r -= 1;
                    self._all_apply(r, f);
                }
                l >>= 1;
                r >>= 1;
            }
        }
        for i in 1..self.height {
            if (l >> i << i) != l {
                self._pull(l >> i)
            };
            if (r >> i << i) != r {
                self._pull((r - 1) >> i)
            };
        }
    }
    fn product(&mut self, mut l: usize, mut r: usize) -> T {
        assert!(l <= r && r <= self.size);
        if l == r {
            return self.id;
        }
        l |= self.size;
        r += self.size;
        for i in (1..self.height).rev() {
            if (l >> i << i) != l {
                self._push(l >> i);
            }
            if (r >> i << i) != r {
                self._push((r - 1) >> i);
            }
        }
        let mut res_l = self.id;
        let mut res_r = self.id;
        while l != r {
            if l & 1 == 1 {
                res_l = (self.op)(&res_l, &self.tree[l]);
                l += 1;
            }
            if r & 1 == 1 {
                r -= 1;
                res_r = (self.op)(&self.tree[r], &res_r);
            }
            l >>= 1;
            r >>= 1;
        }
        (self.op)(&res_l, &res_r)
    }
    fn _pull(&mut self, i: usize) {
        self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
    }
    fn _push(&mut self, i: usize) {
        self._all_apply(i << 1, self.lazy[i]);
        self._all_apply(i << 1 | 1, self.lazy[i]);
        self.lazy[i] = self.off;
    }
    fn _all_apply(&mut self, i: usize, f: U) {
        (self.mapping)(&mut self.tree[i], &f);
        if i & self.size == 0 {
            (self.composition)(&mut self.lazy[i], &f);
        }
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<u32>();
        adj[u].push((w, v));
        adj[v].push((w, u));
    }
    let mut dist = vec![0; n];
    let mut edge = dist.clone();
    let mut tin = vec![usize::MAX; n];
    let mut tout = tin.clone();
    {
        let mut stk = Vec::with_capacity(n);
        stk.push(0);
        let mut t = 0;
        while let Some(u) = stk.pop() {
            if tin[u] != usize::MAX {
                tout[u] = t;
                continue;
            }
            tin[u] = t;
            t += 1;
            stk.push(u);
            if let Some(p) = adj[u].iter().position(|e| tin[e.1] != usize::MAX) {
                adj[u].swap_remove(p);
            }
            for &(w, v) in adj[u].iter() {
                edge[v] = w;
                dist[v] = dist[u] ^ w;
                stk.push(v);
            }
        }
    }
    let mut seg = LazySeg::new(
        n,
        ([0; 20], 0),
        0,
        |lhs, rhs| {
            let mut res = ([0; 20], lhs.1 + rhs.1);
            for (x, (l, r)) in res.0.iter_mut().zip(lhs.0.iter().zip(rhs.0.iter())) {
                *x = *l + *r;
            }
            res
        },
        |node, tag| {
            let mut tag = *tag;
            let len = node.1;
            node.0.iter_mut().for_each(|x| {
                if tag & 1 == 1 {
                    *x = len - *x
                }
                tag >>= 1;
            })
        },
        |tag, f| *tag ^= *f,
    );
    for i in 0..n {
        let mut v = dist[i];
        seg[tin[i]].0.iter_mut().for_each(|x| {
            *x = v & 1;
            v >>= 1;
        });
        seg[i].1 = 1;
    }
    seg.build();
    let q = sc.next::<usize>();
    for _ in 0..q {
        match sc.next::<u32>() {
            1 => {
                let x = sc.next::<usize>() - 1;
                let mut v = sc.next::<u32>();
                v ^= std::mem::replace(&mut edge[x], v);
                seg.apply(tin[x], tout[x], v);
            }
            _ => {
                let x = sc.next::<usize>() - 1;
                let y = sc.next::<usize>() - 1;
                let sub_x = (tout[x] - tin[x]) as u64;
                let sub_y = (tout[y] - tin[y]) as u64;
                let x = seg.product(tin[x], tout[x]).0;
                let y = seg.product(tin[y], tout[y]).0;
                let mut ans = 0;
                for (i, (x, y)) in x.iter().zip(y.iter()).enumerate() {
                    let x = *x as u64;
                    let y = *y as u64;
                    ans += (x * (sub_y - y) + y * (sub_x - x)) << i;
                }
                writeln!(out, "{}", ans).ok();
            }
        }
    }
}

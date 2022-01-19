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

pub struct PerfectSeg<T, F> {
    size: usize,
    tree: Vec<T>,
    id: T,
    op: F,
}

impl<T, F> std::ops::Index<usize> for PerfectSeg<T, F> {
    type Output = T;
    fn index(&self, i: usize) -> &T {
        assert!(i < self.size);
        &self.tree[i | self.size]
    }
}
impl<T, F> std::ops::IndexMut<usize> for PerfectSeg<T, F> {
    fn index_mut(&mut self, i: usize) -> &mut T {
        assert!(i < self.size);
        &mut self.tree[i | self.size]
    }
}

#[allow(dead_code)]
impl<T, F> PerfectSeg<T, F>
where
    T: Clone + std::marker::Copy,
    F: Fn(&T, &T) -> T,
{
    pub fn new(size: usize, id: T, op: F) -> Self {
        let size = size.next_power_of_two();
        PerfectSeg {
            size,
            tree: vec![id; size << 1],
            id,
            op,
        }
    }
    pub fn build(&mut self) {
        for i in (1..self.size).rev() {
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    pub fn clear(&mut self) {
        self.tree[1..].fill(self.id);
    }
    pub fn set(&mut self, mut i: usize, x: T) {
        assert!(i < self.size);
        i |= self.size;
        self.tree[i] = x;
        while i != 1 {
            i >>= 1;
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    pub fn update(&mut self, mut i: usize, x: T) {
        assert!(i < self.size);
        i |= self.size;
        self.tree[i] = (self.op)(&self.tree[i], &x);
        while i != 1 {
            i >>= 1;
            self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
        }
    }
    pub fn product(&self, mut l: usize, mut r: usize) -> T {
        assert!(l <= r && r <= self.size);
        let mut res_l = self.id;
        let mut res_r = self.id;
        l += self.size;
        r += self.size;
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
    pub fn all_prod(&self) -> T {
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
        a: [(i64,i64,i64); n],
    }
    let mut a = a;
    a.sort_unstable_by_key(|&(x, y, _)| (x, y));
    let mut slopes = vec![];
    for j in 1..n {
        for i in 0..j {
            if a[i].0 == a[j].0 {
                break;
            }
            slopes.push((a[j].1 - a[i].1, a[j].0 - a[i].0, i, j));
        }
    }
    slopes.sort_unstable_by(|lhs, rhs| {
        (lhs.0 * rhs.1)
            .cmp(&(rhs.0 * lhs.1))
            .then_with(|| (lhs.2, lhs.3).cmp(&(rhs.2, rhs.3)))
    });
    const INF: i64 = 0x3f3f3f3f3f3f3f3f;
    let mut seg = PerfectSeg::new(n + 1, (INF, !INF, 0), |&lhs, &rhs| {
        (
            lhs.0.min(rhs.0),
            lhs.1.max(rhs.1),
            (rhs.1 - lhs.0).max(std::cmp::max(lhs.2, rhs.2)),
        )
    });
    seg[0] = (0, 0, 0);
    for i in 0..n {
        seg[i + 1] = (seg[i].0 + a[i].2, seg[i].0 + a[i].2, 0);
    }
    seg.build();
    let mut ans = seg.all_prod().2;
    let mut idx = (0..n).collect::<Vec<_>>();
    let mut i = 0;
    while i != slopes.len() {
        let s = (slopes[i].0, slopes[i].1);
        while i != slopes.len() && slopes[i].0 * s.1 == s.0 * slopes[i].1 {
            let k = idx[slopes[i].2];
            let dl = seg[k + 1].0 - seg[k].0;
            let dr = if k == n - 1 { 0 } else { seg[k + 2].0 } - seg[k + 1].0;
            seg.set(k + 1, (seg[k + 1].0 + dr - dl, seg[k + 1].0 + dr - dl, 0));
            idx.swap(slopes[i].2, slopes[i].3);
            i += 1;
        }
        ans.chmax(seg.all_prod().2);
    }
    writeln!(out, "{}", ans).ok();
}

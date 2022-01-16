use std::io::Write;

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

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
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

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let r = sc.next::<i64>();
    let c = sc.next::<i64>();
    let t = sc.next::<usize>();
    const INF: i64 = 0x3f3f3f3f3f3f3f3f;
    let mut seg = PerfectSeg::new(n, [[0; 3]; 3], |&lhs, &rhs| {
        let mut res = [[INF; 3]; 3];
        for ll in 0..3 {
            for lr in 0..3 {
                for rl in 0..3 {
                    if lr == rl {
                        continue;
                    }
                    for rr in 0..3 {
                        res[ll][rr].chmin(lhs[ll][lr] + rhs[rl][rr]);
                    }
                }
            }
        }
        res
    });
    let make_node = |x: i64| {
        let mut node = [[INF; 3]; 3];
        if x < 0 {
            node[0][0] = x.abs() * c;
            node[1][1] = 0;
            node[2][2] = r.min((x.abs() + 1) * c);
        } else if x > 0 {
            node[0][0] = x.abs() * c;
            node[1][1] = r.min((x.abs() + 1) * c);
            node[2][2] = 0;
        } else {
            node[0][0] = 0;
            node[1][1] = c;
            node[2][2] = c;
        }
        node
    };
    for i in 0..n {
        seg[i] = make_node(sc.next::<i64>());
    }
    seg.build();
    writeln!(out, "{}", *seg.all_prod().iter().flatten().min().unwrap()).ok();
    for _ in 0..t {
        seg.set(sc.next::<usize>() - 1, make_node(sc.next::<i64>()));
        writeln!(out, "{}", *seg.all_prod().iter().flatten().min().unwrap()).ok();
    }
}

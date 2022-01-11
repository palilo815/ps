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
    let t = sc.next::<usize>();
    for _ in 0..t {
        run(&mut sc, &mut out);
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

mod segment_tree {
    pub struct SegmentTree<T, F> {
        size: usize,
        tree: Vec<T>,
        id: T,
        op: F,
    }

    impl<T, F> std::ops::Index<usize> for SegmentTree<T, F> {
        type Output = T;
        fn index(&self, i: usize) -> &T {
            assert!(i < self.size);
            &self.tree[i + self.size]
        }
    }
    impl<T, F> std::ops::IndexMut<usize> for SegmentTree<T, F> {
        fn index_mut(&mut self, i: usize) -> &mut T {
            assert!(i < self.size);
            &mut self.tree[i + self.size]
        }
    }

    #[allow(dead_code)]
    impl<T, F> SegmentTree<T, F>
    where
        T: Clone + std::marker::Copy,
        F: Fn(&T, &T) -> T,
    {
        pub fn new(size: usize, id: T, op: F) -> Self {
            SegmentTree {
                size,
                tree: vec![id; size << 1],
                id,
                op,
            }
        }
        pub fn build_with(data: Vec<T>, id: T, op: F) -> Self {
            let size = data.len();
            let mut tree = vec![id; size << 1];
            tree[size..].copy_from_slice(&data);
            for i in (1..size).rev() {
                tree[i] = op(&tree[i << 1], &tree[i << 1 | 1]);
            }
            Self { size, tree, id, op }
        }
        pub fn build(&mut self) {
            for i in (1..self.size).rev() {
                self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
            }
        }
        pub fn set(&mut self, mut i: usize, x: T) {
            assert!(i < self.size);
            i += self.size;
            self.tree[i] = x;
            while i != 1 {
                i >>= 1;
                self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
            }
        }
        pub fn update(&mut self, mut i: usize, x: T) {
            assert!(i < self.size);
            i += self.size;
            self.tree[i] = (self.op)(&self.tree[i], &x);
            while i != 1 {
                i >>= 1;
                self.tree[i] = (self.op)(&self.tree[i << 1], &self.tree[i << 1 | 1]);
            }
        }
        pub fn product(&self, mut l: usize, mut r: usize) -> T {
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
        pub fn all_prod(&self) -> T {
            self.tree[1]
        }
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    const MAX: usize = 10_000;
    let n = sc.next::<usize>();
    let mut y_val = vec![vec![]; MAX + 1];
    for _ in 0..n {
        y_val[sc.next::<usize>()].push(sc.next::<usize>());
    }
    let mut seg = segment_tree::SegmentTree::new(MAX + 1, 0, |&x, &y| std::cmp::max(x, y));
    for x in 0..=10 {
        for &y in y_val[x].iter() {
            for i in y.saturating_sub(10)..=y {
                seg.set(i, seg[i] + 1);
            }
        }
    }
    let mut ans = seg.all_prod();
    for x in 11..=MAX {
        for &y in y_val[x].iter() {
            for i in y.saturating_sub(10)..=y {
                seg.set(i, seg[i] + 1);
            }
        }
        for &y in y_val[x - 11].iter() {
            for i in y.saturating_sub(10)..=y {
                seg.set(i, seg[i] - 1);
            }
        }
        ans.chmax(seg.all_prod());
    }
    writeln!(out, "{}", ans).ok();
}

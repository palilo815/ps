use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

struct SegTree<T, F> {
    size: usize,
    data: Box<[T]>,
    f: F,
}

impl<T, F> SegTree<T, F>
where
    T: Clone + Copy,
    F: Fn(T, T) -> T,
{
    fn new(size: usize, e: T, f: F) -> Self {
        let size = size.next_power_of_two();
        Self {
            size,
            data: vec![e; size << 1].into(),
            f,
        }
    }
    fn set(&mut self, i: usize, x: T) {
        let mut i = i + self.size;
        self.data[i] = x;
        while i != 1 {
            i >>= 1;
            self.data[i] = (self.f)(self.data[i << 1], self.data[i << 1 | 1]);
        }
    }
    fn all_prod(&self) -> T {
        self.data[1]
    }
}

#[derive(Clone, Copy)]
struct Node {
    pref: i32,
    suff: i32,
    best: i32,
    len: i32,
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let kangaroos = (0..n).map(|_| (sc.read::<usize>(), sc.read::<usize>())).collect::<Vec<_>>();
    let mut val = vec![(0, 0); n << 1];
    for i in 0..n {
        val[i << 1] = (kangaroos[i].0, i);
        val[i << 1 | 1] = (kangaroos[i].1, !i);
    }
    val.sort_unstable();
    let mut idx = vec![0; n << 1];
    for (i, (l, r)) in kangaroos.into_iter().enumerate() {
        let l = val.partition_point(|&v| v < (l, i));
        let r = val.partition_point(|&v| v < (r, !i));
        idx[l] = !i as isize;
        idx[r] = i as isize;
    }
    let mut queries = (0..m)
        .map(|i| {
            let l = sc.read::<usize>();
            let r = sc.read::<usize>();
            let l = val.partition_point(|&v| v < (l, 0));
            let r = val.partition_point(|&v| v <= (r, usize::MAX)) - 1;
            (l as isize, r as isize, i)
        })
        .collect::<Vec<_>>();
    queries.sort_unstable_by(|l, r| {
        const B: isize = 256;
        let lb = l.0 / B;
        let rb = r.0 / B;
        lb.cmp(&rb).then(if lb & 1 == 0 { l.1.cmp(&r.1) } else { r.1.cmp(&l.1) })
    });
    const ON: Node = Node {
        pref: 1,
        suff: 1,
        best: 1,
        len: 1,
    };
    const OFF: Node = Node {
        pref: 0,
        suff: 0,
        best: 0,
        len: 1,
    };
    let mut seg = SegTree::new(n, OFF, |l, r| Node {
        pref: l.pref + if l.pref == l.len { r.pref } else { 0 },
        suff: r.suff + if r.suff == r.len { l.suff } else { 0 },
        best: (l.suff + r.pref).max(l.best.max(r.best)),
        len: l.len + r.len,
    });
    let mut ans = vec![0; m];
    let mut l = 0;
    let mut r = -1;
    for (ql, qr, qi) in queries {
        while ql < l {
            l -= 1;
            if idx[l as usize] >= 0 {
                seg.set(idx[l as usize] as usize, ON);
            }
        }
        while r < qr {
            r += 1;
            if idx[r as usize] < 0 {
                seg.set(!idx[r as usize] as usize, ON);
            }
        }
        while l < ql {
            if idx[l as usize] >= 0 {
                seg.set(idx[l as usize] as usize, OFF);
            }
            l += 1;
        }
        while qr < r {
            if idx[r as usize] < 0 {
                seg.set(!idx[r as usize] as usize, OFF);
            }
            r -= 1;
        }
        ans[qi] = seg.all_prod().best;
    }
    for x in ans {
        writeln!(bw, "{x}").ok();
    }
}

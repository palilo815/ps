use std::io::Write;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn next<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

mod flow {
    use std::cmp::PartialEq;
    use std::collections::VecDeque;
    use std::ops::AddAssign;
    use std::ops::SubAssign;

    pub trait Capacity: Clone + Copy + Ord + PartialEq + AddAssign + SubAssign {
        fn zero() -> Self;
        fn inf() -> Self;
    }

    macro_rules! impl_capa {
        ($t:ty, $x:expr) => {
            impl Capacity for $t {
                fn zero() -> Self {
                    0
                }
                fn inf() -> Self {
                    $x
                }
            }
        };
    }

    impl_capa!(i32, i32::MAX);
    impl_capa!(u32, u32::MAX);
    impl_capa!(i64, i64::MAX);
    impl_capa!(u64, u64::MAX);

    #[derive(Clone, Copy)]
    struct Edge<C> {
        v: usize,
        rev: usize,
        cap: C,
    }

    pub struct Dinitz<C> {
        n: usize,
        g: Vec<Vec<Edge<C>>>,
    }

    impl<C: Capacity> Dinitz<C> {
        pub fn new(n: usize) -> Self {
            Self {
                n,
                g: vec![vec![]; n],
            }
        }
        pub fn add_edge(&mut self, u: usize, v: usize, cap: C) {
            assert!(u < self.n && v < self.n);
            let ulen = self.g[u].len();
            let vlen = self.g[v].len();
            self.g[u].push(Edge { v, rev: vlen, cap });
            self.g[v].push(Edge {
                v: u,
                rev: ulen,
                cap: C::zero(),
            });
        }
        pub fn flow(&mut self, s: usize, t: usize) -> C {
            assert!(s < self.n && t < self.n);
            let mut lvl = vec![0; self.n];
            let mut idx = vec![0; self.n];
            let mut que = VecDeque::new();
            let mut res = C::zero();
            while self.bfs(s, t, &mut lvl, &mut que) {
                idx.fill(0);
                loop {
                    let f = self.dfs(s, t, C::inf(), &lvl, &mut idx);
                    if f == C::zero() {
                        break;
                    }
                    res += f;
                }
            }
            res
        }
        fn bfs(&self, s: usize, t: usize, lvl: &mut [u32], que: &mut VecDeque<usize>) -> bool {
            lvl.fill(0);
            lvl[s] = 1;
            que.push_back(s);
            while let Some(u) = que.pop_front() {
                for e in self.g[u].iter() {
                    if e.cap != C::zero() && lvl[e.v] == 0 {
                        lvl[e.v] = lvl[u] + 1;
                        que.push_back(e.v);
                    }
                }
            }
            lvl[t] != 0
        }
        fn dfs(&mut self, u: usize, t: usize, f: C, lvl: &[u32], idx: &mut [usize]) -> C {
            if u == t {
                return f;
            }
            while let Some(&Edge { v, rev, cap }) = self.g[u].get(idx[u]) {
                if cap != C::zero() && lvl[v] == lvl[u] + 1 {
                    let f = self.dfs(v, t, f.min(cap), lvl, idx);
                    if f != C::zero() {
                        self.g[u][idx[u]].cap -= f;
                        self.g[v][rev].cap += f;
                        return f;
                    }
                }
                idx[u] += 1;
            }
            C::zero()
        }
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let (s, t) = (0, n + m + 1);
    let mut dinitz = flow::Dinitz::<u32>::new(n + m + 2);
    for i in 1..n + 1 {
        let c = sc.next::<u32>();
        dinitz.add_edge(s, i, c);
    }
    let mut ans = 0;
    for i in n + 1..n + m + 1 {
        let a = sc.next::<usize>();
        let b = sc.next::<usize>();
        let c = sc.next::<u32>();
        ans += c;
        dinitz.add_edge(a, i, c);
        dinitz.add_edge(b, i, c);
        dinitz.add_edge(i, t, c);
    }
    writeln!(out, "{}", ans - dinitz.flow(s, t)).ok();
}

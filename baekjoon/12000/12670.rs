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
    fn next_bytes(&mut self) -> Vec<u8> {
        self.it.next().unwrap().bytes().collect()
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
    let t = sc.next::<usize>();
    for tc in 1..t + 1 {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();
        let (s, t) = (n * m, n * m + 1);
        let grid = (0..n).map(|_| sc.next_bytes()).collect::<Vec<_>>();
        let mut dinitz = flow::Dinitz::<u32>::new(n * m + 2);
        for i in 0..n {
            for j in 0..m {
                match (i ^ j) & 1 {
                    0 => match grid[i][j] {
                        b'#' => dinitz.add_edge(s, i * m + j, u32::MAX),
                        b'.' => dinitz.add_edge(i * m + j, t, u32::MAX),
                        _ => dinitz.add_edge(s, i * m + j, 4),
                    },
                    _ => match grid[i][j] {
                        b'#' => dinitz.add_edge(i * m + j, t, u32::MAX),
                        b'.' => dinitz.add_edge(s, i * m + j, u32::MAX),
                        _ => dinitz.add_edge(i * m + j, t, 4),
                    },
                }
            }
        }
        const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
        for i in 0..n {
            for j in (0..m).skip(i & 1).step_by(2) {
                for &(dx, dy) in MOVE.iter() {
                    let x = i.wrapping_add(dx);
                    let y = j.wrapping_add(dy);
                    if x == usize::MAX || x == n || y == usize::MAX || y == m {
                        continue;
                    }
                    dinitz.add_edge(i * m + j, x * m + y, 2);
                }
            }
        }
        let res = grid.into_iter().flatten().filter(|&x| x != b'.').count() << 2;
        writeln!(out, "Case #{}: {}", tc, res as u32 - dinitz.flow(s, t)).ok();
    }
}

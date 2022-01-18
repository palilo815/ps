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

mod heavy_light {
    type Edge = (u64, usize);

    const ROOT: usize = 0;

    #[derive(Clone)]
    pub struct Info {
        par: usize,
        top: usize,
        pub dist: u64,
        pub size: u32,
        pub tin: u32,
    }

    pub struct HLD {
        pub info: Vec<Info>,
    }

    impl HLD {
        pub fn new(adj: &mut Vec<Vec<Edge>>) -> Self {
            let mut hld = vec![
                Info {
                    par: usize::MAX,
                    size: 0,
                    top: 0,
                    tin: 0,
                    dist: 0,
                };
                adj.len()
            ];
            let mut dfs_order = vec![0; adj.len()];
            let mut stk = Vec::with_capacity(adj.len());
            stk.push(ROOT);
            for it in dfs_order.iter_mut() {
                let u = stk.pop().unwrap();
                *it = u;
                if let Some(p) = adj[u].iter().position(|&v| v.1 == hld[u].par) {
                    adj[u].swap_remove(p);
                }
                for &(w, v) in adj[u].iter() {
                    hld[v].par = u;
                    hld[v].dist = hld[u].dist + w;
                    stk.push(v);
                }
            }
            for &u in dfs_order.iter().rev() {
                hld[u].size = adj[u].iter().fold(1, |acc, &(_, v)| acc + hld[v].size);
                if let Some((h, _)) = adj[u]
                    .iter()
                    .enumerate()
                    .max_by_key(|(_, &(_, v))| hld[v].size)
                {
                    let last = adj[u].len() - 1;
                    adj[u].swap(h, last);
                }
            }
            stk.push(ROOT);
            let mut timer = 0;
            while let Some(u) = stk.pop() {
                hld[u].tin = timer;
                timer += 1;
                for &(_, v) in adj[u].iter() {
                    stk.push(v);
                    hld[v].top = v;
                }
                if !adj[u].is_empty() {
                    hld[*stk.last().unwrap()].top = hld[u].top;
                }
            }
            Self { info: hld }
        }
        pub fn get_lca(&self, mut u: usize, mut v: usize) -> usize {
            let info = &self.info;
            while info[u].top != info[v].top {
                if info[info[u].top].size > info[info[v].top].size {
                    std::mem::swap(&mut u, &mut v);
                }
                u = info[info[u].top].par;
            }
            if info[u].tin < info[v].tin {
                u
            } else {
                v
            }
        }
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
    let q = sc.next::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 1..n {
        let u = sc.next::<usize>();
        let v = sc.next::<usize>();
        let w = sc.next::<u64>();
        adj[u].push((w, v));
        adj[v].push((w, u));
    }
    let hld = heavy_light::HLD::new(&mut adj);
    let mut colour = vec![0_u8; n]; // 0: dummy, 1: S, 2: T
    let mut nodes = vec![];
    let mut dp: Vec<(usize, u64, u64)> = vec![];
    for _ in 0..q {
        nodes.clear();
        dp.clear();
        let s = sc.next::<usize>();
        let t = sc.next::<usize>();
        let mut s = sc.next_vec::<usize>(s);
        let mut t = sc.next_vec::<usize>(t);
        s.iter().for_each(|&x| colour[x] = 1);
        t.iter().for_each(|&x| colour[x] = 2);
        nodes.append(&mut s);
        nodes.append(&mut t);
        nodes.sort_unstable_by_key(|&x| hld.info[x].tin);
        let mut lcas = nodes
            .windows(2)
            .map(|x| hld.get_lca(x[0], x[1]))
            .collect::<Vec<_>>();
        nodes.append(&mut lcas);
        nodes.sort_unstable_by_key(|&x| std::cmp::Reverse(hld.info[x].tin));
        nodes.dedup();
        const INF: u64 = 0x3f3f3f3f3f3f3f3f;
        let mut ans = INF;
        for &u in nodes.iter() {
            let mut closest_s = if colour[u] == 1 { 0 } else { INF };
            let mut closest_t = if colour[u] == 2 { 0 } else { INF };
            while dp.last().map_or(false, |&(v, _, _)| {
                hld.info[v].tin < hld.info[u].tin + hld.info[u].size
            }) {
                let (v, child_s, child_t) = dp.pop().unwrap();
                let dist_uv = hld.info[v].dist - hld.info[u].dist;
                closest_s.chmin(child_s + dist_uv);
                closest_t.chmin(child_t + dist_uv);
            }
            ans.chmin(closest_s + closest_t);
            dp.push((u, closest_s, closest_t));
            colour[u] = 0;
        }
        writeln!(out, "{}", ans).ok();
    }
}

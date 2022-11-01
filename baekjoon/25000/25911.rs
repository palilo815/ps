use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let edges = (0..n)
        .map(|_| (sc.read::<usize>() - 1, sc.read::<i64>()))
        .collect::<Vec<_>>();
    let r = sc.read_vec::<i64>(n);
    let mut root = vec![usize::MAX; n];
    let mut dist = vec![0; n];
    let mut colour = vec![-1; n];
    let mut c = 0;
    for i in 0..n {
        if colour[i] != -1 {
            continue;
        }
        let mut u = i;
        let mut d = 0;
        while colour[u] == -1 {
            colour[u] = c;
            dist[u] = d;
            d += edges[u].1;
            u = edges[u].0;
        }
        if colour[u] == c {
            c += 1;
            let stem = dist[u];
            while root[u] == usize::MAX {
                root[u] = u;
                dist[u] -= stem;
                u = edges[u].0;
            }
            let mut v = i;
            while root[v] != u {
                root[v] = u;
                dist[v] = stem - dist[v];
                v = edges[v].0;
            }
        } else {
            let stem = d + if u == root[u] { 0 } else { dist[u] };
            let old_c = colour[u];
            let mut v = i;
            while colour[v] == c {
                colour[v] = old_c;
                root[v] = root[u];
                dist[v] = stem - dist[v];
                v = edges[v].0;
            }
        }
    }
    let mut queries = vec![vec![]; c as usize];
    let m = sc.read::<usize>();
    for v in (0..m).map(|_| sc.read::<usize>() - 1) {
        queries[colour[v] as usize].push(v);
    }
    let mut nodes = vec![vec![]; c as usize];
    (0..n).for_each(|x| nodes[colour[x] as usize].push(x));
    let mut walk = vec![0; n];
    for (mut queries, mut nodes) in queries.into_iter().zip(nodes.into_iter()) {
        if queries.iter().any(|&x| x == root[x]) {
            let last = *nodes
                .iter()
                .filter(|&&x| x == root[x])
                .max_by_key(|&&x| dist[x])
                .unwrap();
            let cycle_len = dist[last] + edges[last].1;
            queries.retain(|&x| x == root[x]);
            let walk_cycle = queries.windows(2).fold(0, |acc, w| {
                acc + if dist[w[0]] <= dist[w[1]] {
                    dist[w[1]] - dist[w[0]]
                } else {
                    cycle_len - (dist[w[0]] - dist[w[1]])
                }
            });
            let first_step = dist[*queries.first().unwrap()];
            for u in nodes.into_iter() {
                walk[u] = walk_cycle
                    + if dist[root[u]] > first_step {
                        cycle_len - (dist[root[u]] - first_step)
                            + if u == root[u] { 0 } else { dist[u] }
                    } else {
                        first_step - dist[root[u]] + if u == root[u] { 0 } else { dist[u] }
                    };
            }
        } else {
            nodes.retain(|&x| x != root[x]);
            nodes.sort_unstable_by_key(|&x| dist[x]);
            queries.iter().for_each(|&x| colour[x] = -1);
            for u in nodes.into_iter() {
                if colour[edges[u].0] == -1 {
                    walk[u] = walk[edges[u].0] + edges[u].1;
                    colour[u] = -1;
                }
            }
        }
    }
    for (r, w) in r.into_iter().zip(walk.into_iter()) {
        writeln!(out, "{}", r * w).ok();
    }
}

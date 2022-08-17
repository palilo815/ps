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
    let m = sc.read::<usize>();
    let mut edges = (0..m)
        .map(|_| {
            (
                sc.read::<usize>() - 1,
                sc.read::<usize>() - 1,
                sc.read::<u32>(),
            )
        })
        .collect::<Vec<_>>();
    edges.sort_unstable_by(|lhs, rhs| lhs.2.cmp(&rhs.2));
    let s = sc.read::<usize>() - 1;
    let t = sc.read::<usize>() - 1;
    const INF: u64 = 0x3f3f3f3f3f3f3f3f;
    let mut tmp = vec![INF; n];
    let mut dist = tmp.clone();
    dist[s] = 0;
    let mut i = 0;
    while i != m {
        let mut j = i + 1;
        while j != m && edges[i].2 == edges[j].2 {
            j += 1;
        }
        for &(u, v, w) in edges[i..j].iter() {
            tmp[u] = tmp[u].min(dist[v] + w as u64);
            tmp[v] = tmp[v].min(dist[u] + w as u64);
        }
        for &(u, v, _) in edges[i..j].iter() {
            dist[u] = dist[u].min(tmp[u]);
            dist[v] = dist[v].min(tmp[v]);
            tmp[u] = INF;
            tmp[v] = INF;
        }
        i = j;
    }
    if dist[t] == INF {
        writeln!(out, "DIGESTA").ok();
    } else {
        writeln!(out, "{}", dist[t]).ok();
    }
}

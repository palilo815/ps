use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut edges = (0..m)
        .map(|_| {
            (
                sc.read::<usize>() - 1,
                sc.read::<usize>() - 1,
                if sc.read::<char>() == 'b' {
                    sc.read::<i32>()
                } else {
                    -sc.read::<i32>()
                },
            )
        })
        .collect::<Vec<_>>();
    edges.sort_unstable_by(|l, r| {
        (if l.0 < l.1 { l.0 } else { !l.0 } as isize).cmp(&(if r.0 < r.1 { r.0 } else { !r.0 } as isize))
    });
    const INF: i32 = 0x3f3f3f3f;
    let mut dist = vec![INF; n];
    dist[0] = 0;
    for _ in 0..n / 2 + 2 {
        for &(u, v, w) in edges.iter() {
            if dist[u] != INF {
                dist[v] = dist[v].min(dist[u] + w);
            }
        }
    }
    for (i, _) in dist.into_iter().enumerate().filter(|x| x.1.is_negative()) {
        writeln!(out, "{}", i + 1).ok();
    }
}

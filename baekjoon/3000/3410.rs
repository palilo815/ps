use std::io::Write;

pub struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    pub fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    pub fn next<T: std::str::FromStr>(&mut self) -> T {
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
    let t = sc.next::<usize>();
    for _ in 0..t {
        run(&mut sc, &mut out);
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<i32>();
        adj[u].push((w, v));
        adj[v].push((w, u));
    }
    let shortest_path = |src: usize| {
        #[derive(Clone, PartialEq)]
        enum State {
            None,
            InDeque,
            Popped,
        }
        const INF: i64 = 0x3f3f3f3f3f3f3f3f;
        let mut state = vec![State::None; n];
        let mut dist = vec![INF; n];
        dist[src] = 0;
        let mut dq = std::collections::VecDeque::new();
        dq.push_back(src);
        while let Some(u) = dq.pop_front() {
            state[u] = State::Popped;
            for &(w, v) in adj[u].iter() {
                let d = dist[u] + w as i64;
                if dist[v] > d {
                    dist[v] = d;
                    if state[v] == State::None {
                        dq.push_back(v);
                    } else if state[v] == State::Popped {
                        dq.push_front(v);
                    }
                    state[v] = State::InDeque;
                }
            }
        }
        dist
    };
    let d0 = shortest_path(0);
    let d1 = shortest_path(1);
    let mut ans = 0;
    let mut d = d0
        .iter()
        .zip(d1.iter())
        .map(|(x, y)| x + y)
        .collect::<Vec<_>>();
    d.select_nth_unstable(n >> 1);
    let pivot = d[n >> 1];
    d.into_iter().for_each(|x| ans += (pivot - x).abs());
    let mut d = d0
        .iter()
        .zip(d1.iter())
        .map(|(x, y)| x - y)
        .collect::<Vec<_>>();
    d.select_nth_unstable(n >> 1);
    let pivot = d[n >> 1];
    d.into_iter().for_each(|x| ans += (pivot - x).abs());
    writeln!(out, "{:.10}", ans as f64 / 2.0 / n as f64).ok();
}

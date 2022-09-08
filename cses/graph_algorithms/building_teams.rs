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
    let mut adj = vec![vec![]; n];
    for _ in 0..m {
        let u = sc.read::<usize>() - 1;
        let v = sc.read::<usize>() - 1;
        adj[u].push(v);
        adj[v].push(u);
    }
    let mut team = vec![0; n];
    let mut stack = Vec::with_capacity(n);
    let mut dfs = |s: usize, team: &mut [i32]| {
        stack.push(s);
        team[s] = 1;
        while let Some(u) = stack.pop() {
            for &v in adj[u].iter() {
                if team[v] == 0 {
                    team[v] = team[u] ^ 3;
                    stack.push(v);
                } else if team[u] == team[v] {
                    return false;
                }
            }
        }
        true
    };
    for i in 0..n {
        if team[i] == 0 && !dfs(i, &mut team) {
            writeln!(out, "IMPOSSIBLE").ok();
        }
    }
    for x in team {
        write!(out, "{} ", x).ok();
    }
}

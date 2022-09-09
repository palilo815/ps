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
    let q = sc.read::<usize>();
    let mut adj = vec![vec![]; n];
    for i in 1..n {
        adj[sc.read::<usize>() - 1].push(i);
    }
    let mut dep = vec![-1; n];
    let mut tin = vec![-1; n];
    dep[0] = 0;
    let mut stack = Vec::with_capacity(n - 1);
    stack.push(0);
    let mut tick = 0;
    while let Some(u) = stack.pop() {
        tin[u] = tick;
        tick += 1;
        for &v in adj[u].iter() {
            if dep[v] == -1 {
                dep[v] = dep[u] + 1;
                stack.push(v);
            }
        }
    }
    let mut ids = (0..n).collect::<Vec<_>>();
    ids.sort_unstable_by(|&l, &r| dep[l].cmp(&dep[r]).then(tin[r].cmp(&tin[l])));
    for _ in 0..q {
        let x = sc.read::<usize>() - 1;
        let k = sc.read::<i32>();
        if dep[x] < k {
            writeln!(out, "-1").ok();
        } else {
            let i = ids
                .binary_search_by(|&i| dep[i].cmp(&(dep[x] - k)).then(tin[x].cmp(&tin[i])))
                .unwrap_err();
            writeln!(out, "{}", ids[i] + 1).ok();
        }
    }
}

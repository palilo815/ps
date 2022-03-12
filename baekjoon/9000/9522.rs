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

struct BipartiteMatching {
    n: usize,
    m: usize,
    adj: Vec<Vec<usize>>,
}

impl BipartiteMatching {
    fn new(n: usize, m: usize) -> Self {
        Self {
            n,
            m,
            adj: vec![vec![]; n],
        }
    }
    fn add_edge(&mut self, u: usize, v: usize) {
        assert!(u < self.n && v < self.m);
        self.adj[u].push(v);
    }
    fn matching(&self) -> Vec<usize> {
        let mut visited = vec![false; self.n];
        let mut mat = vec![usize::MAX; self.n];
        let mut rmat = vec![usize::MAX; self.m];
        let mut update = true;
        while update {
            visited.fill(false);
            update = false;
            for u in 0..self.n {
                update |= mat[u] == usize::MAX && self.dfs(&mut visited, &mut mat, &mut rmat, u);
            }
        }
        mat
    }
    fn dfs(&self, visited: &mut [bool], mat: &mut [usize], rmat: &mut [usize], u: usize) -> bool {
        visited[u] = true;
        for &v in self.adj[u].iter() {
            if rmat[v] == usize::MAX || (!visited[rmat[v]] && self.dfs(visited, mat, rmat, rmat[v]))
            {
                mat[u] = v;
                rmat[v] = u;
                return true;
            }
        }
        false
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let mut check_x = [false; 500];
    let mut check_y = [false; 500];
    let mut matcher = BipartiteMatching::new(500, 500);
    for _ in 0..n {
        let x = sc.next::<usize>() - 1;
        let y = sc.next::<usize>() - 1;
        check_x[x] = true;
        check_y[y] = true;
        matcher.add_edge(x, y);
    }
    if check_x.iter().filter(|&&x| x).count() != check_y.iter().filter(|&&y| y).count() {
        writeln!(out, "Mirko").ok();
        return;
    }
    let mat = matcher.matching();
    if mat
        .into_iter()
        .zip(check_x.iter())
        .any(|(pair, exist)| *exist && pair == usize::MAX)
    {
        writeln!(out, "Mirko").ok();
    } else {
        writeln!(out, "Slavko").ok();
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

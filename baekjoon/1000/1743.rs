use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut mat = vec![vec![0; m]; n];
    for _ in 0..k {
        let x = sc.read::<usize>() - 1;
        let y = sc.read::<usize>() - 1;
        mat[x][y] = 1;
    }
    let mut stack = vec![];
    let mut dfs = |x: usize, y: usize| {
        if mat[x][y] == 0 {
            return 0;
        }
        const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
        mat[x][y] = 0;
        stack.push((x, y));
        let mut acc = 0;
        while let Some((x, y)) = stack.pop() {
            acc += 1;
            for &(dx, dy) in MOVE.iter() {
                let x = x + dx;
                let y = y + dy;
                if x < n && y < m && mat[x][y] == 1 {
                    mat[x][y] = 0;
                    stack.push((x, y));
                }
            }
        }
        acc
    };
    let mut ans = 0;
    for i in 0..n {
        for j in 0..m {
            ans = ans.max(dfs(i, j));
        }
    }
    writeln!(bw, "{ans}").ok();
}

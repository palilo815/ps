macro_rules! input {
    (source = $s:expr, $($r:tt)*) => {
        let mut iter = $s.split_whitespace();
        input_inner!{iter, $($r)*}
    };
    ($($r:tt)*) => {
        let s = {
            use std::io::Read;
            let mut s = String::new();
            std::io::stdin().read_to_string(&mut s).unwrap();
            s
        };
        let mut iter = s.split_whitespace();
        input_inner!{iter, $($r)*}
    };
}

macro_rules! input_inner {
    ($iter:expr) => {};
    ($iter:expr, ) => {};
    ($iter:expr, $var:ident : $t:tt $($r:tt)*) => {
        let $var = read_value!($iter, $t);
        input_inner!{$iter $($r)*}
    };
}

macro_rules! read_value {
    ($iter:expr, ( $($t:tt),* )) => {
        ( $(read_value!($iter, $t)),* )
    };
    ($iter:expr, [ $t:tt ; $len:expr ]) => {
        (0..$len).map(|_| read_value!($iter, $t)).collect::<Vec<_>>()
    };
    ($iter:expr, chars) => {
        read_value!($iter, String).chars().collect::<Vec<char>>()
    };
    ($iter:expr, bytes) => {
        read_value!($iter, String).bytes().collect::<Vec<u8>>()
    };
    ($iter:expr, usize1) => {
        read_value!($iter, usize) - 1
    };
    ($iter:expr, $t:ty) => {
        $iter.next().unwrap().parse::<$t>().expect("Parse error")
    };
}

struct DisjointSet {
    p: Vec<i32>,
}

#[allow(dead_code)]
impl DisjointSet {
    fn new(n: usize) -> Self {
        Self { p: vec![-1; n] }
    }
    fn clear(&mut self) {
        self.p.fill(-1);
    }
    fn find(&mut self, u: usize) -> usize {
        if self.p[u] < 0 {
            u
        } else {
            let rt = self.find(self.p[u] as usize);
            self.p[u] = rt as i32;
            rt
        }
    }
    fn unite(&mut self, u: usize, v: usize) -> bool {
        let mut u = self.find(u);
        let mut v = self.find(v);
        if u == v {
            return false;
        }
        if self.p[u] > self.p[v] {
            std::mem::swap(&mut u, &mut v);
        }
        self.p[u] += self.p[v];
        self.p[v] = u as i32;
        true
    }
    fn same(&mut self, u: usize, v: usize) -> bool {
        self.find(u) == self.find(v)
    }
    fn size_of(&mut self, u: usize) -> usize {
        let root = self.find(u);
        (-self.p[root]) as usize
    }
    fn num_components(&self) -> usize {
        self.p.iter().filter(|x| x.is_negative()).count()
    }
    fn iter_roots(&self) -> impl Iterator<Item = usize> + '_ {
        self.p
            .iter()
            .enumerate()
            .filter_map(|(i, x)| match x.is_negative() {
                true => Some(i),
                false => None,
            })
    }
}

fn main() {
    use std::io::Write;
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    input! {
        n: usize,
        m: usize,
        grid: [bytes; n],
    }
    let mut boost = vec![vec![false; m]; n];
    let mut s = (0, 0);
    let mut t = (0, 0);
    for i in 1..(n - 1) {
        for j in 1..(m - 1) {
            if grid[i][j] == b'#' {
                continue;
            }
            if grid[i][j] == b'S' {
                s = (i, j);
            } else if grid[i][j] == b'E' {
                t = (i, j);
            }
            boost[i][j] = grid[i - 1][j] == b'#'
                || grid[i][j - 1] == b'#'
                || grid[i][j + 1] == b'#'
                || grid[i + 1][j] == b'#';
        }
    }
    let mut dist = vec![vec![u32::MAX; m]; n];
    dist[s.0][s.1] = 0;
    let mut dq = std::collections::VecDeque::new();
    dq.push_back((0, s.0, s.1));
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    while let Some((d, x, y)) = dq.pop_front() {
        if d != dist[x][y] {
            continue;
        }
        for &(dx, dy) in MOVE.iter() {
            let xx = x + dx;
            let yy = y + dy;
            let dd = d + (!boost[x][y] || !boost[xx][yy]) as u32;
            if grid[xx][yy] == b'#' || dist[xx][yy] <= dd {
                continue;
            }
            dist[xx][yy] = dd;
            if d == dd {
                dq.push_front((dd, xx, yy));
            } else {
                dq.push_back((dd, xx, yy));
            }
        }
    }
    writeln!(out, "{}", dist[t.0][t.1]).ok();
}

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

pub trait ChangeMinMax {
    fn chmin(&mut self, x: Self) -> bool;
    fn chmax(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChangeMinMax for T {
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

fn main() {
    use std::io::Write;
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    input! {
        n: usize,
        m: usize,
        grid: [bytes; n],
    }
    let mut s = (usize::MAX, usize::MAX);
    let mut food = vec![];
    for i in 0..n {
        for j in 0..m {
            if grid[i][j] == b'S' {
                s = (i, j);
            } else if grid[i][j] == b'K' {
                food.push((i, j));
            }
        }
    }
    let k = food.len();
    if k < 5 {
        writeln!(out, "-1").ok();
        return;
    }
    let mut q = std::collections::VecDeque::new();
    let mut dist = vec![vec![0; m]; n];
    let mut dijk = |s: (usize, usize)| {
        const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
        for row in dist.iter_mut() {
            row.fill(u32::MAX);
        }
        dist[s.0][s.1] = 0;
        q.push_front(s);
        while let Some((x, y)) = q.pop_front() {
            for &(dx, dy) in MOVE.iter() {
                let xx = x.overflowing_add(dx).0;
                let yy = y.overflowing_add(dy).0;
                if xx == usize::MAX
                    || xx == n
                    || yy == usize::MAX
                    || yy == m
                    || grid[xx][yy] == b'X'
                    || dist[xx][yy] != u32::MAX
                {
                    continue;
                }
                dist[xx][yy] = dist[x][y] + 1;
                q.push_back((xx, yy));
            }
        }
        food.iter().map(|&(x, y)| dist[x][y]).collect::<Vec<_>>()
    };
    let st = dijk(s);
    let adj = food.iter().map(|&x| dijk(x)).collect::<Vec<_>>();
    let mut ans = u32::MAX;
    for i0 in 0..k {
        let mut res = st[i0];
        if res == u32::MAX {
            continue;
        }
        for i1 in 0..k {
            if i0 == i1 || adj[i0][i1] == u32::MAX {
                continue;
            }
            res += adj[i0][i1];
            for i2 in 0..k {
                if i0 == i2 || i1 == i2 || adj[i1][i2] == u32::MAX {
                    continue;
                }
                res += adj[i1][i2];
                for i3 in 0..k {
                    if i0 == i3 || i1 == i3 || i2 == i3 || adj[i2][i3] == u32::MAX {
                        continue;
                    }
                    res += adj[i2][i3];
                    for i4 in 0..k {
                        if i0 != i4 && i1 != i4 && i2 != i4 && i3 != i4 && adj[i3][i4] != u32::MAX {
                            ans.chmin(res + adj[i3][i4]);
                        }
                    }
                    res -= adj[i2][i3];
                }
                res -= adj[i1][i2];
            }
            res -= adj[i0][i1];
        }
    }
    writeln!(out, "{}", if ans == u32::MAX { -1 } else { ans as i32 }).ok();
}

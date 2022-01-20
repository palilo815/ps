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

#[derive(Eq, PartialEq)]
struct MinHeapElem(u32, usize, usize);

impl std::cmp::Ord for MinHeapElem {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0.cmp(&(self.0))
    }
}

impl std::cmp::PartialOrd for MinHeapElem {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
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
        s: (usize1, usize1),
        t: (usize1, usize1),
    }
    let mut dp = vec![vec![[usize::MAX, usize::MAX, usize::MAX, usize::MAX]; m]; n];
    for i in 1..(n - 1) {
        for j in 1..(m - 1) {
            if grid[i][j] == b'.' {
                dp[i][j][0] = dp[i - 1][j][0] + 1;
                dp[i][j][1] = dp[i][j - 1][1] + 1;
            }
        }
    }
    for i in (1..(n - 1)).rev() {
        for j in (1..(m - 1)).rev() {
            if grid[i][j] == b'.' {
                dp[i][j][2] = dp[i][j + 1][2] + 1;
                dp[i][j][3] = dp[i + 1][j][3] + 1;
            }
        }
    }
    const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
    const INF: u32 = 0x3f3f3f3f;
    let mut dist = vec![vec![INF; m]; n];
    dist[s.0][s.1] = 0;
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(MinHeapElem(0, s.0, s.1));
    while let Some(MinHeapElem(d, x, y)) = pq.pop() {
        if d != dist[x][y] {
            continue;
        }
        if x == t.0 && y == t.1 {
            writeln!(out, "{}", d).ok();
            return;
        }
        for (&dir, &jump) in MOVE.iter().zip(dp[x][y].iter()) {
            let xx = x + dir.0 * jump;
            let yy = y + dir.1 * jump;
            if dist[xx][yy] > dist[x][y] + 1 {
                dist[xx][yy] = dist[x][y] + 1;
                pq.push(MinHeapElem(dist[xx][yy], xx, yy));
            }
            let xx = x + dir.0;
            let yy = y + dir.1;
            if grid[xx][yy] == b'.' && dist[xx][yy] > dist[x][y] + 2 {
                dist[xx][yy] = dist[x][y] + 2;
                pq.push(MinHeapElem(dist[xx][yy], xx, yy));
            }
        }
    }
    writeln!(out, "-1").ok();
}

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
    const N: usize = 20;
    const MOVE: [(usize, usize); 8] = [
        (2_usize.wrapping_neg(), 1_usize.wrapping_neg()),
        (2_usize.wrapping_neg(), 1),
        (1_usize.wrapping_neg(), 2_usize.wrapping_neg()),
        (1_usize.wrapping_neg(), 2),
        (1, 2_usize.wrapping_neg()),
        (1, 2),
        (2, 1_usize.wrapping_neg()),
        (2, 1),
    ];
    let mut dist = [[0; N]; N];
    let mut dq = std::collections::VecDeque::new();
    let t = sc.read::<usize>();
    for t in 1..=t {
        let n = sc.read::<usize>();
        let src = (sc.read::<usize>() - 1, sc.read::<usize>() - 1);
        let dst = (sc.read::<usize>() - 1, sc.read::<usize>() - 1);
        dist.fill([-1; N]);
        dist[src.0][src.1] = 0;
        dq.push_back(src);
        while let Some((x, y)) = dq.pop_front() {
            let d = dist[x][y];
            for &(dx, dy) in MOVE.iter() {
                let x = x + dx;
                let y = y + dy;
                if x < n && y < n && dist[x][y] == -1 {
                    dist[x][y] = d + 1;
                    dq.push_back((x, y));
                }
            }
        }
        let ans = dist[dst.0][dst.1];
        writeln!(bw, "Case #{t}: {ans}\n").ok();
    }
}

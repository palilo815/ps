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

fn main() {
    use std::io::Write;
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    input! {
        n: usize,
        grid: [bytes; n],
    }
    let mut grid = grid;
    let mut stk = vec![];
    let mut dfs = |grid: &mut [Vec<u8>], s: (usize, usize)| -> (u32, u32) {
        stk.push(s);
        grid[s.0][s.1] = 0;
        let mut area = 1;
        let mut peri = 4;
        const MOVE: [(usize, usize); 4] = [(usize::MAX, 0), (0, usize::MAX), (0, 1), (1, 0)];
        while let Some((x, y)) = stk.pop() {
            for &(dx, dy) in MOVE.iter() {
                let (xx, yy) = (x.wrapping_add(dx), y.wrapping_add(dy));
                if xx == usize::MAX || xx == n || yy == usize::MAX || yy == n {
                    continue;
                }
                if grid[xx][yy] == 0 {
                    peri -= 1;
                } else if grid[xx][yy] == b'#' {
                    grid[xx][yy] = 0;
                    stk.push((xx, yy));
                    area += 1;
                    peri += 3;
                }
            }
        }
        (area, peri)
    };
    let mut ans = (0, 0);
    for i in 0..n {
        for j in 0..n {
            if grid[i][j] == b'#' {
                let res = dfs(&mut grid, (i, j));
                if res.0 > ans.0 || res.0 == ans.0 && res.1 < ans.1 {
                    ans = res;
                }
            }
        }
    }
    writeln!(out, "{} {}", ans.0, ans.1).ok();
}

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
        m: usize,
        grid: [chars; n],
    }
    let mut grid = grid;
    let s = grid.iter().flatten().position(|&x| x == 'I').unwrap();
    const MOVE: [(isize, isize); 4] = [(-1, 0), (0, -1), (0, 1), (1, 0)];
    let mut stk = vec![];
    stk.push((s / m, s % m));
    let mut ans = 0;
    while let Some((x, y)) = stk.pop() {
        for &(dx, dy) in MOVE.iter() {
            let xx = x as isize + dx;
            let yy = y as isize + dy;
            if xx == -1 || yy == -1 {
                continue;
            }
            let xx = xx as usize;
            let yy = yy as usize;
            if xx != n && yy != m && grid[xx][yy] != 'X' {
                if grid[xx][yy] == 'P' {
                    ans += 1;
                }
                grid[xx][yy] = 'X';
                stk.push((xx, yy));
            }
        }
    }
    if ans == 0 {
        writeln!(out, "TT").ok();
    } else {
        writeln!(out, "{}", ans).ok();
    }
}

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
    ($iter:expr, $var:ident:$t:tt $($r:tt)*) => {
        let $var = read_value!($iter, $t);
        input_inner!{$iter $($r)*}
    };
}

macro_rules! read_value {
    ($iter:expr, ($($t:tt), *)) => {
        ($(read_value!($iter, $t)), *)
    };
    ($iter:expr, [$t:tt; $len:expr]) => {
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
        grid: [[i32; n]; n],
    }
    const MAX: usize = 49 * 49 * 2000;
    const OFFSET: i32 = (MAX >> 1) as i32;
    let mut pref = vec![vec![0; n + 1]; n + 1];
    let mut suff = vec![vec![0; n + 1]; n + 1];
    let mut cnt = vec![0_u32; MAX + 1];
    let mut solve = |grid: &[Vec<i32>]| -> u32 {
        for i in 0..n {
            for j in 0..n {
                pref[i + 1][j + 1] = grid[i][j] - pref[i][j] + pref[i][j + 1] + pref[i + 1][j];
            }
        }
        for i in (0..n).rev() {
            for j in (0..n).rev() {
                suff[i][j] = grid[i][j] + suff[i][j + 1] + suff[i + 1][j] - suff[i + 1][j + 1];
            }
        }
        let mut ans = 0;
        for x in 1..n {
            for y in 1..n {
                for i in 0..x {
                    for j in 0..y {
                        let sum = pref[i][j] - pref[i][y] - pref[x][j] + pref[x][y];
                        cnt[(sum + OFFSET) as usize] += 1;
                    }
                }
                for i in x + 1..n + 1 {
                    for j in y + 1..n + 1 {
                        let sum = pref[x][y] - pref[x][j] - pref[i][y] + pref[i][j];
                        ans += cnt[(sum + OFFSET) as usize];
                    }
                }
                for i in 0..x {
                    for j in 0..y {
                        let sum = pref[i][j] - pref[i][y] - pref[x][j] + pref[x][y];
                        cnt[(sum + OFFSET) as usize] = 0;
                    }
                }
            }
        }
        ans
    };
    let r0 = solve(&grid);
    let mut grid = grid;
    grid.iter_mut().for_each(|x| x.reverse());
    let r1 = solve(&grid);
    writeln!(out, "{}", r0 + r1).ok();
}

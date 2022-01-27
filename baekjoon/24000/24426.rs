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
        grid: [[i32; n]; n],
        mid: (usize1, usize1),
    }
    const INF: i32 = 0x3f3f3f3f;
    let mut dp = vec![(!INF, !INF); n + 1];
    for i in 0..n {
        for j in 0..n {
            if (i, j) == (0, 0) {
                dp[1].0 = grid[0][0];
                continue;
            }
            if (i, j) == mid {
                dp[j + 1].1 = dp[j].0.max(dp[j + 1].0) + grid[i][j];
                dp[j + 1].0 = !INF;
            } else {
                dp[j + 1].0 = dp[j].0.max(dp[j + 1].0) + grid[i][j];
                dp[j + 1].1 = dp[j].1.max(dp[j + 1].1) + grid[i][j];
            }
        }
    }
    assert!(dp[n].0.is_positive() && dp[n].1.is_positive());
    writeln!(out, "{} {}", dp[n].1, dp[n].0).ok();
}

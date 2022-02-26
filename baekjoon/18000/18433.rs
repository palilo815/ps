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

trait ChMinMax {
    fn chmin(&mut self, x: Self) -> bool;
    fn chmax(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChMinMax for T {
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
        m: u32,
        x: [u32; n],
        t: [u32; n],
    }
    let mut x = x;
    x.insert(0, 0);
    x.push(m);
    const INF: u32 = 0x3f3f3f3f;
    let mut dp = vec![vec![vec![(INF, INF); n + 1]; n + 1]; n + 1];
    dp[0][0][0] = (0, 0);
    for visit in 0..n {
        for l in 0..visit + 1 {
            let r = visit - l;
            for s in 0..visit + 1 {
                if dp[l][r][s].0 != INF {
                    let nxt = dp[l][r][s].0 + x[l + 1] - x[l];
                    dp[l + 1][r][s + (nxt <= t[l]) as usize].0.chmin(nxt);
                    let nxt = dp[l][r][s].0 + m - x[n - r] + x[l];
                    dp[l][r + 1][s + (nxt <= t[n - 1 - r]) as usize]
                        .1
                        .chmin(nxt);
                }
                if dp[l][r][s].1 != INF {
                    let nxt = dp[l][r][s].1 + x[l + 1] + m - x[n + 1 - r];
                    dp[l + 1][r][s + (nxt <= t[l]) as usize].0.chmin(nxt);
                    let nxt = dp[l][r][s].1 + x[n + 1 - r] - x[n - r];
                    dp[l][r + 1][s + (nxt <= t[n - 1 - r]) as usize]
                        .1
                        .chmin(nxt);
                }
            }
        }
    }
    let ans = (0..n + 1).fold(0, |acc, i| {
        acc.max(
            dp[i][n - i]
                .iter()
                .rposition(|x| x.0 != INF || x.1 != INF)
                .unwrap_or(0),
        )
    });
    writeln!(out, "{}", ans).ok();
}

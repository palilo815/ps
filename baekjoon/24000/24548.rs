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
    ($iter:expr, bytes) => {
        read_value!($iter, String).bytes().collect::<Vec<u8>>()
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
        _n: usize,
        s: bytes,
    }
    let mut dp = [[[[0_u64; 3]; 3]; 3]; 3];
    dp[0][0][0][0] = 1;
    let (mut t, mut g, mut f, mut p) = (0, 0, 0, 0);
    let mut ans = 0;
    for x in s.into_iter() {
        match x {
            b'T' => t = if t == 2 { 0 } else { t + 1 },
            b'G' => g = if g == 2 { 0 } else { g + 1 },
            b'F' => f = if f == 2 { 0 } else { f + 1 },
            b'P' => p = if p == 2 { 0 } else { p + 1 },
            _ => unreachable!(),
        }
        ans += dp[t][g][f][p];
        dp[t][g][f][p] += 1;
    }
    writeln!(out, "{}", ans).ok();
}

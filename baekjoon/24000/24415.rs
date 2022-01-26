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
        c: usize,
        k: usize,
        s: bytes,
        a: [(char, u32, u32); c],
    }
    let mut dp = (0..n).map(|x| (x, 0)).collect::<Vec<_>>();
    for &(op, i, x) in a.iter() {
        let i = i as usize;
        if op == 'S' {
            let j = x as usize;
            dp.swap(i, j);
        } else {
            dp[i].1 += x;
        }
    }
    dp.iter_mut().for_each(|(_, x)| *x %= 26);
    let mut s = s;
    let mut t = s.clone();
    let mut tmp = dp.clone();
    let mut cycle = k / c;
    while cycle != 0 {
        if cycle & 1 == 1 {
            for i in 0..n {
                t[i] = s[dp[i].0] + dp[i].1 as u8;
                if t[i] > b'Z' {
                    t[i] -= 26;
                }
            }
            std::mem::swap(&mut s, &mut t);
        }
        for i in 0..n {
            tmp[i] = (dp[dp[i].0].0, dp[i].1 + dp[dp[i].0].1);
            if tmp[i].1 > 26 {
                tmp[i].1 -= 26;
            }
        }
        std::mem::swap(&mut dp, &mut tmp);
        cycle >>= 1;
    }
    for (op, i, x) in a.into_iter().take(k % c) {
        let i = i as usize;
        if op == 'S' {
            s.swap(i, x as usize);
        } else {
            s[i] += x as u8;
            if s[i] > b'Z' {
                s[i] -= 26;
            }
        }
    }
    writeln!(out, "{}", String::from_utf8(s).unwrap()).ok();
}

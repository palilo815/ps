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
        a: [bytes; n],
    }
    if n == 1 {
        writeln!(out, "0").ok();
        return;
    }
    let a = a
        .into_iter()
        .map(|x| {
            let len = x.len() as i32;
            let first = *x.first().unwrap();
            let mut val = 0_i64;
            let mut pw = 1_i64;
            let mut f = false;
            for c in x {
                f |= c != first;
                if f {
                    val *= 2;
                    pw *= 2;
                }
                val += if c == b'B' { 1 } else { -1 };
            }
            (val, pw, len)
        })
        .collect::<Vec<_>>();
    let max_denom = a.iter().max_by_key(|x| x.1).unwrap().1;
    let a = a
        .into_iter()
        .map(|x| (x.0 * (max_denom / x.1), x.2))
        .collect::<Vec<_>>();
    let mut ans = 0;
    let f = |a: &[(i64, i32)]| -> Vec<(i64, i32)> {
        let mut res = vec![(0, 0)];
        for x in a {
            let mut acc = res
                .iter()
                .map(|y| (x.0 + y.0, x.1 + y.1))
                .collect::<Vec<_>>();
            res.append(&mut acc);
        }
        res.sort_unstable_by_key(|&x| std::cmp::Reverse(x));
        res.dedup_by_key(|x| x.0);
        res
    };
    let u = f(&a[..(n >> 1)]);
    let v = f(&a[(n >> 1)..]);
    let mut j = v.len() - 1;
    for i in 0..u.len() {
        while j != usize::MAX && u[i].0 + v[j].0 < 0 {
            j -= 1;
        }
        if j != usize::MAX && u[i].0 + v[j].0 == 0 {
            ans.chmax(u[i].1 + v[j].1);
        }
    }
    writeln!(out, "{}", ans).ok();
}

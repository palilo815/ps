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
        a: [(i64, i64, i64); n],
    }
    let mut in_time = Vec::with_capacity(n);
    let mut out_time = Vec::with_capacity(n);
    let mut ans = 1;
    for &(aim, _, v0) in a.iter() {
        in_time.clear();
        out_time.clear();
        let mut cnt = 0;
        for &(s, e, v1) in a.iter() {
            let dv = v0 - v1;
            if dv > 0 {
                if e < aim {
                    continue;
                }
                in_time.push((s - aim, dv));
                out_time.push((e - aim, dv));
            } else if dv < 0 {
                if s > aim {
                    continue;
                }
                in_time.push((aim - e, -dv));
                out_time.push((aim - s, -dv));
            } else if s <= aim && aim <= e {
                cnt += 1;
            }
        }
        in_time.sort_unstable_by(|lhs, rhs| (lhs.0 * rhs.1).cmp(&(rhs.0 * lhs.1)));
        out_time.sort_unstable_by(|lhs, rhs| (lhs.0 * rhs.1).cmp(&(rhs.0 * lhs.1)));
        let mut i = 0;
        let mut j = 0;
        ans.chmax(cnt);
        while i != in_time.len() {
            if in_time[i].0 * out_time[j].1 <= out_time[j].0 * in_time[i].1 {
                i += 1;
                cnt += 1;
                ans.chmax(cnt);
            } else {
                j += 1;
                cnt -= 1;
            }
        }
    }
    writeln!(out, "{}", ans).ok();
}

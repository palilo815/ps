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
        m: usize,
        a: [i32; n],
        b: [i32; m],
    }
    let mut v = vec![vec![]; n + m];
    let (mut i, mut j, mut k) = (0, 0, m);
    while i != n || j != m {
        if j == m || i != n && a[i] < b[j] {
            v[k].push(a[i]);
            k += 1;
            i += 1;
        } else {
            k -= 1;
            v[k].push(b[j]);
            j += 1;
        }
    }
    let ans = v.into_iter().fold(0, |acc, v| {
        let mut res = (1..v.len())
            .step_by(2)
            .fold(0, |acc, i| acc + v[i] - v[i - 1]);
        if v.len() & 1 == 0 {
            return acc + res;
        }
        let mut tmp = res;
        for i in (0..v.len()).rev().skip(1).step_by(2) {
            tmp += v[i + 1] + v[i - 1] - (v[i] << 1);
            res.chmin(tmp);
        }
        acc + res
    });
    writeln!(out, "{}", ans).ok();
}

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
        x: u32,
        a: [u32; n],
    }
    let parametric = |mut lo, mut hi| {
        let f = |m| -> bool {
            let mut pq = (0..m)
                .map(|x| std::cmp::Reverse(a[x]))
                .collect::<std::collections::BinaryHeap<_>>();
            for &y in a.iter().skip(m) {
                let mut least = pq.peek_mut().unwrap();
                (*least).0 += y;
                if (*least).0 > x {
                    return false;
                }
            }
            true
        };
        // first true
        while lo != hi {
            let m = lo + (hi - lo) / 2;
            if f(m) {
                hi = m;
            } else {
                lo = m + 1;
            }
        }
        lo
    };
    writeln!(out, "{}", parametric(1, n)).ok();
}

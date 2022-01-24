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
        a2: i32,
        a1: i32,
        a0: i32,
        c1: i32,
        c2: i32,
        n0: i32,
    }
    let b = -a1;
    let c = -a0;
    let o = {
        let a = c2 - a2;
        if a < 0 {
            // 위로 볼록
            false
        } else if a == 0 {
            // 일차함수
            b >= 0 && b * n0 + c >= 0
        } else {
            // 극소: x = -b / 2a
            if n0 * 2 * a < -b {
                a * b * b - b * b * 2 * a + c * 2 * a * 2 * a >= 0
            } else {
                a * n0 * n0 + b * n0 + c >= 0
            }
        }
    };
    let omega = {
        let a = c1 - a2;
        if a > 0 {
            // 아래로 볼록
            false
        } else if a == 0 {
            // 일차함수
            b <= 0 && b * n0 + c <= 0
        } else {
            // 극대: x = b / -2a
            if n0 * -2 * a < b {
                a * b * b - b * b * 2 * a + c * 2 * a * 2 * a <= 0
            } else {
                a * n0 * n0 + b * n0 + c <= 0
            }
        }
    };
    writeln!(out, "{}", (o && omega) as u32).ok();
}

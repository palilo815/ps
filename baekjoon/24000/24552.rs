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
        s: bytes,
    }
    let mut pref = vec![-1; s.len() + 1];
    pref[0] = 0;
    for (i, &x) in s.iter().enumerate() {
        pref[i + 1] = pref[i] + if x == b'(' { 1 } else { -1 };
        if pref[i + 1] < 0 {
            break;
        }
    }
    let mut ans = 0;
    let mut suff = 0;
    for (i, x) in s.into_iter().enumerate().rev() {
        if suff == pref[i] {
            ans += 1;
        }
        suff += if x == b')' { 1 } else { -1 };
        if suff < 0 {
            break;
        }
    }
    writeln!(out, "{}", ans).ok();
}

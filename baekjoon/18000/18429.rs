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
    ($iter:expr, [$t:tt; $len:expr]) => {
        (0..$len).map(|_| read_value!($iter, $t)).collect::<Vec<_>>()
    };
    ($iter:expr, $t:ty) => {
        $iter.next().unwrap().parse::<$t>().expect("Parse error")
    };
}

fn next_permutation<T: std::cmp::Ord>(data: &mut [T]) -> bool {
    let i = match data.windows(2).rposition(|w| w[0] < w[1]) {
        Some(i) => i,
        None => {
            data.reverse();
            return false;
        }
    };
    let j = data.iter().rposition(|x| data[i] < *x).unwrap();
    data.swap(i, j);
    data[i + 1..].reverse();
    true
}

fn main() {
    use std::io::Write;
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    input! {
        n: usize,
        k: i32,
        a: [i32; n],
    }
    let mut id = (0..n).collect::<Vec<_>>();
    let mut ans = 0;
    loop {
        let mut w = 500;
        if id.iter().all(|&i| {
            w = w + a[i] - k;
            w >= 500
        }) {
            ans += 1;
        }
        if !next_permutation(&mut id) {
            break;
        }
    }
    writeln!(out, "{}", ans).ok();
}

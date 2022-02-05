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
        s: bytes,
    }
    // sum[l, r) = pref_even[r] - pref_even[l] if l is even
    //             pref_odd[r]  - pref_odd[l]  if l is odd
    let mut pref_even = vec![0; n + 1];
    let mut pref_odd = vec![0; n + 1];
    for (i, x) in s.into_iter().enumerate() {
        if x == b'H' {
            pref_even[i + 1] = pref_even[i] + 3;
            pref_odd[i + 1] = pref_odd[i] + 3;
        } else {
            pref_even[i + 1] = pref_even[i] + if i & 1 == 0 { 5 } else { 1 };
            pref_odd[i + 1] = pref_odd[i] + if i & 1 == 0 { 1 } else { 5 };
        }
    }
    // maximum: 5 + 3 + 5 + 3 + ... + 5
    let mut ans = vec![];
    for x in 1..=4 * n + 1 {
        let mut i = 0;
        for y in 1.. {
            let pref = if i & 1 == 0 { &pref_even } else { &pref_odd };
            let zero = pref[i];
            i += pref[i..].partition_point(|psum| *psum < zero + x);
            if i == n {
                ans.push((x, y));
                break;
            } else if i == n + 1 {
                break;
            }
        }
    }
    writeln!(out, "{}", ans.len()).ok();
    for (x, y) in ans {
        writeln!(out, "{} {}", x, y).ok();
    }
}

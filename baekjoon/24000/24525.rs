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
        s: bytes,
    }
    let mut pref = vec![0; s.len() + 1];
    for (i, x) in s.into_iter().enumerate() {
        pref[i + 1] = pref[i]
            + match x {
                b'S' => 2,
                b'K' => -1,
                _ => 0,
            };
    }
    let mn = *pref.iter().min().unwrap();
    let mx = *pref.iter().max().unwrap();
    let offset = -mn;
    let mut first_idx = vec![usize::MAX; (mx - mn + 1) as usize];
    let mut ans = 0;
    let mut i = 0;
    while i != pref.len() {
        let sum = (pref[i] + offset) as usize;
        let mut j = i + 1;
        while j != pref.len() {
            if pref[i] != pref[j] {
                break;
            }
            j += 1;
        }
        if first_idx[sum] == usize::MAX {
            first_idx[sum] = i;
        } else {
            ans = ans.max(j - 1 - first_idx[sum]);
        }
        i = j;
    }
    writeln!(out, "{}", if ans == 0 { -1 } else { ans as i32 }).ok();
}

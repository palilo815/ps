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
        n: usize,
        a: bytes,
        b: bytes,
    }
    let mut ok = true;
    ok &= a[0] == b[0] && a[n - 1] == b[n - 1];
    let mut cnt = [0; 26];
    for (&a, &b) in a.iter().zip(b.iter()) {
        cnt[(a - b'a') as usize] += 1;
        cnt[(b - b'a') as usize] -= 1;
    }
    ok &= cnt.iter().all(|&x| x == 0);
    let mut a = a;
    let mut b = b;
    a.retain(|&x| x != b'a' && x != b'e' && x != b'i' && x != b'o' && x != b'u');
    b.retain(|&x| x != b'a' && x != b'e' && x != b'i' && x != b'o' && x != b'u');
    ok &= a == b;
    writeln!(out, "{}", if ok { "YES" } else { "NO" }).ok();
}

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
        m: i32,
        a: [(i32, i32); n],
    }
    let mut a = a;
    a.sort_unstable_by_key(|x| x.1);
    let mut acc_cheaper = 0;
    let mut acc_same = 0;
    for i in 0..n {
        if i != 0 && a[i - 1].1 != a[i].1 {
            acc_cheaper += acc_same;
            acc_same = 0;
        }
        if acc_cheaper + a[i].0 >= m {
            writeln!(out, "{}", a[i].1).ok();
            return;
        }
        acc_same += a[i].0;
    }
    let st = a.iter().position(|x| x.1 == a.last().unwrap().1).unwrap();
    let mut cost = 0;
    let mut acc = acc_cheaper;
    a[st..].sort_unstable_by_key(|x| std::cmp::Reverse(x.0));
    for &(w, c) in &a[st..] {
        acc += w;
        cost += c;
        if acc >= m {
            writeln!(out, "{}", cost).ok();
            return;
        }
    }
    writeln!(out, "-1").ok();
}

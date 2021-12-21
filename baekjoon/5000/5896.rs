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
        k: u32,
        m: i64,
        a: [(i32, i32); n],
    }
    let mut m = m;
    let mut p = (0..n).collect::<Vec<_>>();
    let mut c = p.clone();
    p.sort_unstable_by_key(|&i| a[i].0);
    c.sort_unstable_by_key(|&i| a[i].1);
    let mut used = vec![false; n];
    let mut discount = (0..k)
        .map(|_| std::cmp::Reverse(0))
        .collect::<std::collections::BinaryHeap<_>>();
    let mut ans = 0;
    let mut i = 0;
    let mut j = 0;
    while ans != n {
        while used[p[i]] {
            i += 1;
        }
        while used[c[j]] {
            j += 1;
        }
        let cost = {
            let &std::cmp::Reverse(undo) = discount.peek().unwrap();
            if a[c[j]].1 + undo < a[p[i]].0 {
                discount.pop();
                discount.push(std::cmp::Reverse(a[c[j]].0 - a[c[j]].1));
                j += 1;
                used[c[j - 1]] = true;
                a[c[j - 1]].1 + undo
            } else {
                i += 1;
                used[p[i - 1]] = true;
                a[p[i - 1]].0
            }
        };
        m -= cost as i64;
        if m < 0 {
            break;
        }
        ans += 1;
    }
    writeln!(out, "{}", ans).ok();
}

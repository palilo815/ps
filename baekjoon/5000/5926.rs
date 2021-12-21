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

pub trait ChangeMinMax {
    fn chmin(&mut self, x: Self) -> bool;
    fn chmax(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChangeMinMax for T {
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
        a: [(u32, usize); n],
    }
    let mut a = a;
    a.sort_unstable();
    let mut ids = a.iter().map(|&(_, x)| x).collect::<Vec<_>>();
    ids.sort_unstable();
    ids.dedup();
    for (_, x) in a.iter_mut() {
        *x = ids.binary_search(x).unwrap();
    }
    let mut cnt = ids;
    cnt.fill(0);
    let mut unseen = cnt.len();
    let mut ans = u32::MAX;
    let mut j = 0;
    for i in 0..n {
        while j != n && unseen != 0 {
            if cnt[a[j].1] == 0 {
                unseen -= 1;
            }
            cnt[a[j].1] += 1;
            j += 1;
        }
        if unseen != 0 {
            break;
        }
        ans.chmin(a[j - 1].0 - a[i].0);
        cnt[a[i].1] -= 1;
        if cnt[a[i].1] == 0 {
            unseen += 1;
        }
    }
    writeln!(out, "{}", ans).ok();
}

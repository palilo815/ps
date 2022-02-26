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

trait ChMinMax {
    fn chmin(&mut self, x: Self) -> bool;
    fn chmax(&mut self, x: Self) -> bool;
}

impl<T: PartialOrd> ChMinMax for T {
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
        k: i32,
        s: bytes,
    }
    let (mut j, mut o, mut i) = (0, 0, 0);
    let (mut js, mut os, mut is) = (0, 0, 0);
    let mut ans = usize::MAX;
    for it in 0.. {
        while j != n && js != k {
            js += (s[j] == b'J') as i32;
            os -= (s[j] == b'O') as i32;
            j += 1;
        }
        while o != n && os != k {
            os += (s[o] == b'O') as i32;
            is -= (s[o] == b'I') as i32;
            o += 1;
        }
        while i != n && is != k {
            is += (s[i] == b'I') as i32;
            i += 1;
        }
        if is != k {
            break;
        }
        ans.chmin(i - it);
        js -= (s[it] == b'J') as i32;
    }
    if ans == usize::MAX {
        writeln!(out, "-1").ok();
    } else {
        writeln!(out, "{}", ans - 3 * k as usize).ok();
    }
}

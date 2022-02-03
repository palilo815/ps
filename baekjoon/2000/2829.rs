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
        grid: [[i32; n]; n],
    }
    let mut ans = 0;
    for i in 1..n - 1 {
        for j in 1..n - 1 {
            let mut sum = 0;
            for k in 1.. {
                sum += grid[i - k][j - k] - grid[i - k][j + k] - grid[i + k][j - k]
                    + grid[i + k][j + k];
                ans.chmax(sum);
                if i - k == 0 || i + k == n - 1 || j - k == 0 || j + k == n - 1 {
                    break;
                }
            }
        }
    }
    for i in 0..n - 1 {
        for j in 0..n - 1 {
            let mut sum = 0;
            for k in 0.. {
                sum += grid[i - k][j - k] - grid[i - k][j + 1 + k] - grid[i + 1 + k][j - k]
                    + grid[i + 1 + k][j + 1 + k];
                ans.chmax(sum);
                if i - k == 0 || i + 1 + k == n - 1 || j - k == 0 || j + 1 + k == n - 1 {
                    break;
                }
            }
        }
    }
    writeln!(out, "{}", ans).ok();
}

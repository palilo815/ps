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
        m: usize,
        grid: [bytes; n],
    }
    for i in 0..n {
        for j in 0..m {
            if grid[i][j] == b'0' {
                continue;
            }
            let mut check = 0;
            'outer: for i2 in (i.max(9) - 9)..n.min(i + 10) {
                for j2 in (j.max(9) - 9)..m.min(j + 10) {
                    if grid[i2][j2] == b'1' {
                        let bit = 1
                            << std::cmp::max(((i - i2) as isize).abs(), ((j - j2) as isize).abs());
                        if (check & bit) == 0 {
                            check |= bit;
                        } else {
                            check = 0;
                            break 'outer;
                        }
                    }
                }
            }
            if check == (1 << 10) - 1 {
                writeln!(out, "{} {}", i, j).ok();
                return;
            }
        }
    }
    writeln!(out, "-1").ok();
}

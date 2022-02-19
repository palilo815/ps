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
        m: usize,
        n: usize,
        o: usize,
        p: usize,
        q: usize,
        r: usize,
        s: usize,
        t: usize,
        u: usize,
        v: usize,
        w: usize,
        grid: [[[[[[[[[[[i32; m]; n]; o]; p]; q]; r]; s]; t]; u]; v]; w],
    }
    let mut grid = grid;
    const MOVE: [[usize; 11]; 22] = [
        [usize::MAX, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, usize::MAX, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, usize::MAX, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, usize::MAX, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, usize::MAX, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, usize::MAX, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, usize::MAX, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, usize::MAX, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, usize::MAX, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, usize::MAX, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, usize::MAX],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    ];
    let mut dq = std::collections::VecDeque::new();
    for a in 0..w {
        for b in 0..v {
            for c in 0..u {
                for d in 0..t {
                    for e in 0..s {
                        for f in 0..r {
                            for g in 0..q {
                                for h in 0..p {
                                    for i in 0..o {
                                        for j in 0..n {
                                            for k in 0..m {
                                                if grid[a][b][c][d][e][f][g][h][i][j][k] == 1 {
                                                    dq.push_back([a, b, c, d, e, f, g, h, i, j, k]);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    let dim = [w, v, u, t, s, r, q, p, o, n, m];
    let mut ans = -1;
    while !dq.is_empty() {
        ans += 1;
        let sz = dq.len();
        for _ in 0..sz {
            let u = dq.pop_front().unwrap();
            for dir in MOVE.iter() {
                let mut v = u;
                v.iter_mut()
                    .zip(dir.iter())
                    .for_each(|(cur, dir)| *cur += dir);
                if v.iter()
                    .zip(dim.iter())
                    .any(|(&x, &lim)| x == usize::MAX || x == lim)
                {
                    continue;
                }
                let cell =
                    &mut grid[v[0]][v[1]][v[2]][v[3]][v[4]][v[5]][v[6]][v[7]][v[8]][v[9]][v[10]];
                if *cell == 0 {
                    *cell = 1;
                    dq.push_back(v);
                }
            }
        }
    }
    for a in 0..w {
        for b in 0..v {
            for c in 0..u {
                for d in 0..t {
                    for e in 0..s {
                        for f in 0..r {
                            for g in 0..q {
                                for h in 0..p {
                                    for i in 0..o {
                                        for j in 0..n {
                                            for k in 0..m {
                                                if grid[a][b][c][d][e][f][g][h][i][j][k] == 0 {
                                                    writeln!(out, "-1").ok();
                                                    return;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    writeln!(out, "{}", ans).ok();
}

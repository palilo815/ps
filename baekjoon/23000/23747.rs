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
        grid: [chars; n],
        sx: usize1,
        sy: usize1,
        s: chars,
    }
    let mut stk = vec![];
    let mut x = sx;
    let mut y = sy;
    let mut ans = vec![vec!['#'; m]; n];
    for &c in s.iter() {
        match c {
            'U' => x -= 1,
            'D' => x += 1,
            'L' => y -= 1,
            'R' => y += 1,
            _ => {
                ans[x][y] = '.';
                stk.push((x, y));
            }
        }
    }
    const ADJ: [(isize, isize); 4] = [(-1, 0), (0, -1), (0, 1), (1, 0)];
    while let Some((x, y)) = stk.pop() {
        for &(dx, dy) in ADJ.iter() {
            let xx = x as isize + dx;
            let yy = y as isize + dy;
            if xx == -1 || yy == -1 {
                continue;
            }
            let xx = xx as usize;
            let yy = yy as usize;
            if xx != n && yy != m && grid[x][y] == grid[xx][yy] && ans[xx][yy] == '#' {
                ans[xx][yy] = '.';
                stk.push((xx, yy));
            }
        }
    }
    ans[x][y] = '.';
    if x != 0 {
        ans[x - 1][y] = '.';
    }
    if y != 0 {
        ans[x][y - 1] = '.';
    }
    if x + 1 != n {
        ans[x + 1][y] = '.';
    }
    if y + 1 != m {
        ans[x][y + 1] = '.';
    }
    for i in 0..n {
        for j in 0..m {
            write!(out, "{}", ans[i][j]).ok();
        }
        writeln!(out, "").ok();
    }
}

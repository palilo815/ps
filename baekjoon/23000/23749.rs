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
        s: [char; 2 * n],
    }
    let s = {
        let mut mask = 0;
        for &x in s.iter().rev() {
            mask = mask << 1 | (x == 'O') as i32;
        }
        mask
    };
    let is_win = |mut x| {
        let mut score = 0;
        for _ in 0..n {
            score += x & 1;
            x >>= 1;
            score -= x & 1;
            x >>= 1;
        }
        score > 0
    };
    let shift = |mask, pos| {
        let pos_bit = (mask >> pos) & 1;
        let low_bit = mask & ((1 << pos) - 1);
        (mask & (-1 << (pos + 1)) | low_bit << 1 | pos_bit) as usize
    };
    let mut visited = vec![false; 1 << (2 * n)];
    visited[s as usize] = true;
    let mut cur = vec![s];
    let mut nxt = vec![];
    let mut ans = 0;
    loop {
        nxt.clear();
        for &u in cur.iter() {
            if is_win(u) {
                writeln!(out, "{}", ans).ok();
                return;
            }
            for i in 1..(2 * n) {
                let v = shift(u, i);
                if !visited[v] {
                    visited[v] = true;
                    nxt.push(v as i32);
                }
            }
        }
        ans += 1;
        std::mem::swap(&mut cur, &mut nxt);
    }
}

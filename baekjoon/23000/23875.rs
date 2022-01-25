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
        k: usize,
        m: usize,
        n: usize,
        p: [(u32, u32); k],
        f: [u32; m],
    }
    let mut p = p;
    let mut f = f;
    p.sort_unstable_by_key(|x| x.0);
    f.sort_unstable();
    let mut profit = vec![];
    // [0, st), [ed, k)는 한 마리만 배치하면 전부 먹는다.
    let st = p
        .iter()
        .position(|x| x.0 > *f.first().unwrap())
        .unwrap_or(k);
    let ed = p
        .iter()
        .rposition(|x| x.0 < *f.last().unwrap())
        .unwrap_or(usize::MAX)
        + 1;
    profit.push(p.iter().take(st).fold(0, |acc, x| acc + x.1 as u64));
    profit.push(p.iter().skip(ed).fold(0, |acc, x| acc + x.1 as u64));
    p.truncate(ed);
    let mut it = p.iter().skip(st).peekable();
    for enemy in f.windows(2) {
        // enemy[0], enemy[1] 사이의 풀은...
        // 1. 한 마리만 배치해서 최대한 먹는다.
        //  -> 만약 x(enemy[0] < x < enemy[1])에 있는 풀부터 먹고 싶다면
        //  -> 내 소를 x + (x - enemy[0]) - 0.000000001에 배치하는 게 최적이다.
        //  -> 그러면 우로 (x + enemy[1]) / 2 "이전"까지 모든 풀을 먹을 수 있다. (끝점은 x)
        // 2. 두 마리를 배치해서 전부 먹는다.
        if it.peek() == None {
            break;
        }
        let mut max1 = 0;
        let mut sum1 = 0;
        let mut sum2 = 0;
        let mut jt = it.clone();
        while let Some(x) = it.peek() {
            if x.0 > enemy[1] {
                break;
            }
            sum2 += x.1 as u64;
            let lim = enemy[1].min((x.0 + (x.0 - enemy[0]) + enemy[1] + 1) >> 1);
            while jt.peek().unwrap_or(&&(u32::MAX, 0)).0 < lim {
                sum1 += jt.next().unwrap().1 as u64;
            }
            max1.chmax(sum1);
            sum1 -= x.1 as u64;
            it.next();
        }
        profit.push(max1);
        profit.push(sum2 - max1);
    }
    let n = n.min(profit.len());
    profit.select_nth_unstable_by_key(n - 1, |&x| std::cmp::Reverse(x));
    writeln!(out, "{}", profit.into_iter().take(n).sum::<u64>()).ok();
}

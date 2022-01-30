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

#[derive(Eq, PartialEq)]
struct MinHeapElem(u32, usize);

impl std::cmp::Ord for MinHeapElem {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        self.0.cmp(&(rhs.0))
    }
}

impl std::cmp::PartialOrd for MinHeapElem {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
    }
}

fn main() {
    use std::io::Write;
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    input! {
        n: usize,
        k: usize,
        a: [usize1; k],
    }
    const INF: u32 = 0x3f3f3f3f;
    let mut when = vec![INF; k];
    let mut nxt = vec![0; k];
    for i in (0..k).rev() {
        nxt[i] = when[a[i]];
        when[a[i]] = i as u32;
    }
    let mut plugged = when;
    plugged.fill(0);
    let mut pq = std::collections::BinaryHeap::new();
    let mut cnt = 0;
    let mut ans = 0;
    a.into_iter().zip(nxt.into_iter()).for_each(|(id, nxt)| {
        if plugged[id] == 1 {
            pq.push(MinHeapElem(nxt, id));
            return;
        }
        if cnt == n {
            let popped = pq.pop().unwrap().1;
            plugged[popped] = 0;
            cnt -= 1;
            ans += 1;
        }
        pq.push(MinHeapElem(nxt, id));
        plugged[id] = 1;
        cnt += 1;
    });
    write!(out, "{}", ans).ok();
}

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

const MOD: u32 = 1_000_000_007;

pub struct BinaryIndexedTree {
    size: usize,
    tree: Vec<u32>,
}

impl BinaryIndexedTree {
    pub fn new(size: usize) -> Self {
        Self {
            size,
            tree: vec![0; size + 1],
        }
    }
    pub fn clear(&mut self) {
        self.tree.fill(0);
    }
    pub fn update(&mut self, mut i: usize, x: u32) {
        assert!(i <= self.size);
        i += 1;
        while i <= self.size {
            self.tree[i] += x;
            self.tree[i] %= MOD;
            i += i & i.wrapping_neg();
        }
    }
    pub fn prefix(&self, mut i: usize) -> u32 {
        assert!(i <= self.size);
        let mut ret = 0;
        while i != 0 {
            ret += self.tree[i];
            ret %= MOD;
            i &= i - 1;
        }
        ret
    }
}

fn main() {
    use std::io::Write;
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    input! {
        n: usize,
        a: [usize1; n],
    }
    let mut bit = BinaryIndexedTree::new(n);
    let mut dp = vec![1; n];
    for _ in 0..11 {
        bit.clear();
        a.iter().zip(dp.iter_mut()).for_each(|(&x, dp)| {
            bit.update(x, *dp);
            *dp = bit.prefix(x);
        });
    }
    writeln!(out, "{}", bit.prefix(n)).ok();
}

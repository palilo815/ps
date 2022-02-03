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

pub struct BinaryIndexedTree<T> {
    size: usize,
    tree: Vec<T>,
    id: T,
}

#[allow(dead_code)]
impl<T> BinaryIndexedTree<T>
where
    T: std::clone::Clone
        + std::cmp::PartialOrd
        + std::marker::Copy
        + std::ops::AddAssign
        + std::ops::SubAssign
        + std::ops::Sub<Output = T>,
{
    pub fn new(size: usize, id: T) -> Self {
        BinaryIndexedTree {
            size,
            tree: vec![id; size + 1],
            id,
        }
    }
    pub fn build(&mut self) {
        for i in 1..self.size {
            let val = self.tree[i];
            let idx = i + (i & i.wrapping_neg());
            if idx <= self.size {
                self.tree[idx] += val;
            }
        }
    }
    pub fn clear(&mut self) {
        self.tree[1..].fill(self.id);
    }
    pub fn get(&self, i: usize) -> T {
        assert!(i < self.size);
        if i & 1 == 0 {
            self.product(i, i + 1)
        } else {
            self.tree[i + 1]
        }
    }
    pub fn fake_update(&mut self, i: usize, x: T) {
        self.tree[i + 1] += x;
    }
    pub fn update(&mut self, mut i: usize, x: T) {
        assert!(i <= self.size);
        i += 1;
        while i <= self.size {
            self.tree[i] += x;
            i += i & i.wrapping_neg();
        }
    }
    pub fn prefix(&self, mut i: usize) -> T {
        assert!(i <= self.size);
        let mut ret = self.id;
        while i != 0 {
            ret += self.tree[i];
            i &= i - 1;
        }
        ret
    }
    pub fn product(&self, l: usize, r: usize) -> T {
        assert!(l <= r);
        self.prefix(r) - self.prefix(l)
    }
    pub fn lower_bound(&self, mut k: T) -> usize {
        let mut i = 0;
        let mut pw = 1 << 20;
        while pw != 0 {
            if (i | pw) <= self.size && self.tree[i | pw] < k {
                i |= pw;
                k -= self.tree[i];
            }
            pw >>= 1;
        }
        i
    }
    pub fn upper_bound(&self, mut k: T) -> usize {
        let mut i = 0;
        let mut pw = 1 << 20;
        while pw != 0 {
            if (i | pw) <= self.size && self.tree[i | pw] <= k {
                i |= pw;
                k -= self.tree[i];
            }
            pw >>= 1;
        }
        i
    }
}

fn main() {
    use std::io::Write;
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    input! {
        n: usize,
        a:[u32; n],
    }
    let mut a = a;
    let mut ans = 0;
    let mut i = 0;
    while i != n {
        let mut j = i + 2;
        while j != n && a[j - 1] > a[j] {
            j += 1;
        }
        a[i..j].reverse();
        ans += 1;
        i = j;
    }
    let mut bit = BinaryIndexedTree::new(n, 0_u32);
    for x in a.into_iter().rev() {
        let i = x as usize - 1;
        ans += bit.prefix(i) as u64;
        bit.update(i, 1);
    }
    writeln!(out, "{}", ans).ok();
}

use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self {
            it: s.leak().split_ascii_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

struct DynamicKth<T> {
    size: usize,
    data: Box<[T]>,
}

impl DynamicKth<i32> {
    fn new(size: usize) -> Self {
        let size = size.next_power_of_two();
        Self {
            size,
            data: vec![0; size + 1].into(),
        }
    }
    fn add(&mut self, mut i: usize, x: i32) {
        i += 1;
        while i <= self.size {
            self.data[i] += x;
            i += i & i.wrapping_neg();
        }
    }
    fn remove_kth(&mut self, mut k: i32) -> usize {
        let mut i = 0;
        let mut len = self.size >> 1;
        while len != 0 {
            if self.data[i | len] < k {
                i |= len;
                k -= self.data[i];
            } else {
                self.data[i | len] -= 1;
            }
            len >>= 1;
        }
        i
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut dk = DynamicKth::new(2_000_001);
    for _ in 0..n {
        match sc.read::<char>() {
            '1' => {
                dk.add(sc.read::<usize>(), 1);
            }
            _ => {
                writeln!(bw, "{}", dk.remove_kth(sc.read::<i32>())).ok();
            }
        }
    }
}

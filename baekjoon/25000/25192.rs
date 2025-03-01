use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_array<const N: usize>(&mut self) -> [u8; N] {
        let s = self.it.next().unwrap();
        let mut a = [0; N];
        a[..s.len()].copy_from_slice(s.as_bytes());
        a
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const ENTER: [u8; 20] = {
        let mut arr = [0; 20];
        arr[0] = b'E';
        arr[1] = b'N';
        arr[2] = b'T';
        arr[3] = b'E';
        arr[4] = b'R';
        arr
    };
    let n = sc.read::<usize>();
    let mut set = std::collections::HashSet::new();
    let mut ans = 0;
    for _ in 0..n {
        let s = sc.read_array::<20>();
        if s == ENTER {
            set.clear();
        } else if set.insert(s) {
            ans += 1;
        }
    }
    writeln!(bw, "{ans}").ok();
}

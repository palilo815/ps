use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = Vec::new();
        stdin().lock().read_to_end(&mut buf).ok();
        let s = unsafe { std::str::from_utf8_unchecked(Box::leak(buf.into_boxed_slice())) };
        Self { it: s.split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let t = sc.read::<usize>();
    for t in 1..=t {
        let n = sc.read::<usize>();
        if n == 0 {
            writeln!(bw, "Case #{t}: INSOMNIA").ok();
            continue;
        }
        let mut check = [false; 10];
        for n in (n..).step_by(n) {
            let mut x = n;
            while x != 0 {
                check[x % 10] = true;
                x /= 10;
            }
            if check.iter().all(|&f| f) {
                writeln!(bw, "Case #{t}: {n}").ok();
                break;
            }
        }
    }
}

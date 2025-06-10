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
    const N: usize = 50;
    let mut a = [([0; 10], 0); N];
    loop {
        let n = sc.read::<usize>();
        if n == 0 {
            break;
        }
        let a = &mut a[..n];
        a.fill_with(|| {
            let name = sc.read_array::<10>();
            let h = (sc.read::<f64>() * 100.0) as u32;
            (name, h)
        });
        let mx = a.iter().max_by(|l, r| l.1.cmp(&r.1)).unwrap().1;
        for (name, h) in a {
            if *h == mx {
                let i = name.iter().position(|&x| x == 0).unwrap_or(name.len());
                write!(bw, "{} ", String::from_utf8(name[..i].to_vec()).unwrap()).ok();
            }
        }
        writeln!(bw).ok();
    }
}

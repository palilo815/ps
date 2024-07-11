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

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let t = sc.read::<usize>();
    let mut p = [0; 26];
    for t in 1..=t {
        write!(bw, "Case #{t}:").ok();
        let n = sc.read::<usize>();
        let p = &mut p[..n];
        p.iter_mut().for_each(|x| *x = sc.read::<i32>());
        let i = p.iter().enumerate().max_by_key(|x| x.1).unwrap().0;
        let j = p.iter().enumerate().filter(|x| x.0 != i).max_by_key(|x| x.1).unwrap().0;
        (p[j]..p[i]).for_each(|_| write!(bw, " {}", (b'A' + i as u8) as char).unwrap());
        for _ in p[j]..p[i] {}
        for (k, &x) in p.iter().enumerate() {
            if k != i && k != j {
                (0..x).for_each(|_| write!(bw, " {}", (b'A' + k as u8) as char).unwrap());
            }
        }
        (0..p[j]).for_each(|_| write!(bw, " {}{}", (b'A' + i as u8) as char, (b'A' + j as u8) as char).unwrap());
        writeln!(bw).ok();
    }
}

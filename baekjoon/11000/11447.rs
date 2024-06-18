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
    let dx = (1.0, 0.0);
    let dy = (0.5, f64::sqrt(3.0) / 2.0);
    let dz = (-0.5, f64::sqrt(3.0) / 2.0);
    for _ in 0..t {
        let c = sc.read::<usize>();
        let p = (0..c)
            .scan((0.0, 0.0), |p, _| {
                let d = sc.read::<char>();
                let d = match d {
                    'x' => dx,
                    'y' => dy,
                    'z' => dz,
                    _ => unreachable!(),
                };
                let x = sc.read::<f64>();
                p.0 += d.0 * x;
                p.1 += d.1 * x;
                Some(*p)
            })
            .collect::<Vec<_>>();
        let area = p
            .iter()
            .zip(p.iter().skip(1).cycle())
            .fold(0.0, |acc, (u, v)| acc + u.0 * v.1 - u.1 * v.0)
            .abs();
        let area = (area / f64::sqrt(3.0) * 2.0).round();
        writeln!(bw, "{area:.0}").ok();
    }
}

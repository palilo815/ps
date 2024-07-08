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
    const N: usize = 100;
    let mut points = [(0., 0., 0., 0.); N];
    let mut dist = [0.; N];
    let mut conn = [false; N];
    loop {
        let n = sc.read::<usize>();
        if n == 0 {
            break;
        }
        let points = &mut points[..n];
        for (x, y, z, r) in points.iter_mut() {
            *x = sc.read();
            *y = sc.read();
            *z = sc.read();
            *r = sc.read();
        }
        let dist = &mut dist[..n];
        dist[1..].fill(f64::MAX);
        let conn = &mut conn[..n];
        conn.fill(false);
        let mut mst = 0.;
        for _ in 0..n {
            let i = (0..n)
                .filter(|&i| !conn[i])
                .min_by(|&l, &r| dist[l].partial_cmp(&dist[r]).unwrap())
                .unwrap();
            conn[i] = true;
            mst += dist[i];
            for j in 0..n {
                if !conn[j] {
                    let dx = points[i].0 - points[j].0;
                    let dy = points[i].1 - points[j].1;
                    let dz = points[i].2 - points[j].2;
                    let d = (f64::sqrt(dx * dx + dy * dy + dz * dz) - points[i].3 - points[j].3).max(0.);
                    dist[j] = dist[j].min(d);
                }
            }
        }
        writeln!(bw, "{mst:.3}").ok();
    }
}

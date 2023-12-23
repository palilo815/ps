use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &str) -> Scanner {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    const INF: i32 = 0x3f3f3f3f;
    const N: usize = 1_000;
    let mut x = [0; N];
    let mut y = [0; N];
    let mut dist = [0; N];
    let mut con = [false; N];
    loop {
        let n = sc.read::<usize>();
        if n == 0 {
            break;
        }
        let dist = &mut dist[..n];
        let con = &mut con[..n];
        for i in 0..n {
            x[i] = sc.read::<i32>();
            y[i] = sc.read::<i32>();
        }
        con.fill(false);
        dist.fill(INF);
        dist[0] = 0;
        let mut mst = 0.0;
        for _ in 0..n {
            let k = (0..n).filter(|&i| !con[i]).min_by(|&l, &r| dist[l].cmp(&dist[r])).unwrap();
            mst += (dist[k] as f64).sqrt();
            con[k] = true;
            for i in 0..n {
                if !con[i] {
                    let dx = x[i] - x[k];
                    let dy = y[i] - y[k];
                    dist[i] = dist[i].min(dx * dx + dy * dy);
                }
            }
        }
        writeln!(out, "{mst:.2}").ok();
    }
}

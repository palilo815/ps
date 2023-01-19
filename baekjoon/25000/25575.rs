use std::io::*;

struct Scanner<'a> {
    it: std::str::SplitWhitespace<'a>,
}

impl<'a> Scanner<'a> {
    fn new(s: &'a str) -> Scanner<'a> {
        Scanner {
            it: s.split_whitespace(),
        }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).unwrap();
    let mut sc = Scanner::new(&s);
    let out = stdout();
    let mut out = BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    const N: usize = 10_000;
    const K: usize = 100_000;
    let mut xdeg = [0; N];
    let mut ydeg = [0; N];
    let mut xsorted = [0; N];
    let mut ysorted = [0; N];
    let mut edges = [(0, 0); K];
    let t = sc.read::<usize>();
    for _ in 0..t {
        let n = sc.read::<usize>();
        let m = sc.read::<usize>();
        let k = sc.read::<usize>();
        let xdeg = &mut xdeg[..n];
        let ydeg = &mut ydeg[..m];
        xdeg.fill(0);
        ydeg.fill(0);
        for e in edges[..k].iter_mut() {
            e.0 = sc.read::<usize>() - 1;
            e.1 = sc.read::<usize>() - 1;
            xdeg[e.0] += 1;
            ydeg[e.1] += 1;
        }
        let xsorted = &mut xsorted[..n];
        let ysorted = &mut ysorted[..m];
        xsorted.copy_from_slice(xdeg);
        ysorted.copy_from_slice(ydeg);
        xsorted.sort_unstable();
        ysorted.sort_unstable();
        let mut s = xsorted
            .iter()
            .enumerate()
            .fold(0, |acc, (i, &deg)| acc + (i + 1) as u32 * deg);
        s += ysorted
            .iter()
            .enumerate()
            .fold(0, |acc, (i, &deg)| acc + (i + 1) as u32 * deg);
        write!(out, "{s}").ok();
        s -= edges[..k].iter().fold(u32::MAX, |mn, e| {
            let xi = xsorted.partition_point(|&v| v < xdeg[e.0]) as u32 + 1;
            let yi = ysorted.partition_point(|&v| v < ydeg[e.1]) as u32 + 1;
            mn.min(xi + yi)
        });
        writeln!(out, " {s}").ok();
    } 
}

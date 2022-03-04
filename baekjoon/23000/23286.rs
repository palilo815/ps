use std::io::Write;

mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let t = sc.next::<usize>();
    const INF: i32 = 0x3f3f3f3f;
    let mut d = vec![vec![INF; n]; n];
    for i in 0..n {
        d[i][i] = 0;
    }
    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<i32>();
        d[u][v] = d[u][v].min(w);
    }
    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                d[i][j] = d[i][j].min(d[i][k].max(d[k][j]));
            }
        }
    }
    d.iter_mut()
        .flatten()
        .filter(|x| **x == INF)
        .for_each(|x| *x = -1);
    for _ in 0..t {
        let s = sc.next::<usize>() - 1;
        let t = sc.next::<usize>() - 1;
        writeln!(out, "{}", d[s][t]).ok();
    }
}

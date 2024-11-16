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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<i64>();
    let k = sc.read::<i64>();
    let m = sc.read::<usize>();
    let a = sc.read_vec::<i64>(m);
    let m = sc.read::<usize>();
    let b = sc.read_vec::<i64>(m);
    let mut c = vec![];
    let mut d = vec![];
    let mut i = 0;
    let mut j = 0;
    while i != a.len() || j != b.len() {
        if i == a.len() {
            c.push(b[j]);
            j += 1;
        } else if j == b.len() {
            c.push(a[i]);
            i += 1;
        } else {
            match a[i].abs().cmp(&b[j].abs()) {
                std::cmp::Ordering::Less => {
                    c.push(a[i]);
                    i += 1;
                }
                std::cmp::Ordering::Greater => {
                    c.push(b[j]);
                    j += 1;
                }
                std::cmp::Ordering::Equal => {
                    if a[i] == b[j] {
                        c.push(a[i]);
                    }
                    d.push(a[i] / b[j] * a[i].abs());
                    i += 1;
                    j += 1;
                }
            }
        }
    }
    write!(bw, "{}", c.len()).ok();
    for x in c {
        write!(bw, " {x}").ok();
    }
    writeln!(bw).ok();
    write!(bw, "{}", d.len()).ok();
    for x in d {
        write!(bw, " {x}").ok();
    }
    writeln!(bw).ok();
    for v in [a, b] {
        let mid = v.partition_point(|x| x.abs() <= k);
        write!(bw, "{}", v.len()).ok();
        for &x in v.iter().skip(mid) {
            write!(bw, " {}", x.signum() * (x.abs() - k)).ok();
        }
        for x in v.into_iter().take(mid) {
            write!(bw, " {}", x.signum() * (x.abs() + n - k)).ok();
        }
        writeln!(bw).ok();
    }
}

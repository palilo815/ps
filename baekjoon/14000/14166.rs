use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a String) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
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

#[derive(Eq, PartialEq)]
struct MinHeapElem(u64, usize, usize);

impl std::cmp::Ord for MinHeapElem {
    fn cmp(&self, rhs: &Self) -> std::cmp::Ordering {
        rhs.0.cmp(&(self.0))
    }
}

impl std::cmp::PartialOrd for MinHeapElem {
    fn partial_cmp(&self, rhs: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(rhs))
    }
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let k = sc.next::<u64>();
    const INF: u32 = 0x3f3f3f3f;
    let mut ans = 0;
    let mut a = (0..n)
        .map(|_| {
            let mut vt = [INF; 10];
            let m = sc.next::<usize>();
            for i in 0..m {
                vt[i] = sc.next::<u32>();
            }
            vt.sort_unstable();
            let cheapest = vt[0];
            ans += cheapest as u64;
            vt.iter_mut()
                .take_while(|x| **x != INF)
                .for_each(|x| *x -= cheapest);
            vt
        })
        .filter(|x| x[1] != INF)
        .collect::<Vec<_>>();
    ans *= k;
    a.sort_unstable();
    let mut pq = std::collections::BinaryHeap::new();
    pq.push(MinHeapElem(0, 0, 0));
    for _ in 0..k {
        let MinHeapElem(c, i, j) = pq.pop().unwrap();
        ans += c;
        if j + 1 != 10 && a[i][j + 1] != INF {
            pq.push(MinHeapElem(
                c + a[i][j + 1] as u64 - a[i][j] as u64,
                i,
                j + 1,
            ));
        }
        if j != 0 && i + 1 != a.len() {
            if j == 1 {
                pq.push(MinHeapElem(c + (a[i + 1][1] - a[i][1]) as u64, i + 1, 1));
            }
            pq.push(MinHeapElem(c + a[i + 1][1] as u64, i + 1, 1));
        }
    }
    writeln!(out, "{}", ans).ok();
}

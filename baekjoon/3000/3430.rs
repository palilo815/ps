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
struct MinHeapElem(u32, usize);

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
    let t = sc.next::<usize>();
    for _ in 0..t {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();
        let a = sc.next_vec::<usize>(m);
        const INF: u32 = 0x3f3f3f3f;
        let mut when = vec![INF; n + 1];
        let mut nxt = vec![0; m + 1];
        for i in (0..m).rev() {
            if a[i] != 0 {
                nxt[i] = when[a[i]];
                when[a[i]] = i as u32;
            }
        }
        let mut pq = when
            .into_iter()
            .enumerate()
            .filter_map(|(i, first_rain)| {
                if first_rain == INF {
                    None
                } else {
                    Some(MinHeapElem(first_rain, i))
                }
            })
            .collect::<std::collections::BinaryHeap<_>>();
        let mut water = vec![true; n + 1];
        let mut ok = true;
        let mut ans = Vec::with_capacity(a.iter().filter(|x| **x == 0).count());
        for (id, next_rain) in a.into_iter().zip(nxt.into_iter()) {
            if id == 0 {
                let x = pq.pop().unwrap_or(MinHeapElem(0, 0)).1;
                water[x] = false;
                ans.push(x);
            } else {
                if water[id] {
                    ok = false;
                    break;
                } else {
                    water[id] = true;
                }
                pq.push(MinHeapElem(next_rain, id));
            }
        }
        if ok {
            writeln!(out, "YES").ok();
            for x in ans {
                write!(out, "{} ", x).ok();
            }
            writeln!(out, "").ok();
        } else {
            writeln!(out, "NO").ok();
        }
    }
}

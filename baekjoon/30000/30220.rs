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
    fn raw(&mut self) -> [u8; 20] {
        let s = self.it.next().unwrap();
        let mut r = [b' '; 20];
        r[..s.len()].copy_from_slice(s.as_bytes());
        r
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut a = (0..n).map(|_| (sc.raw(), sc.read::<i64>())).collect::<Vec<_>>();
    a.sort_unstable_by(|l, r| r.0.cmp(&l.0));
    let index = a.iter().enumerate().map(|(i, x)| (x.0, i)).collect::<std::collections::HashMap<_, _>>();
    let mut pq = a.iter().enumerate().map(|(i, x)| (x.1, i)).collect::<std::collections::BinaryHeap<_>>();
    for _ in 0..m {
        if sc.read::<usize>() == 1 {
            let i = *index.get(&sc.raw()).unwrap();
            a[i].1 += sc.read::<i64>();
            pq.push((a[i].1, i));
        } else {
            loop {
                let (salary, i) = pq.pop().unwrap();
                if a[i].1 == salary {
                    let name = String::from_utf8(a[i].0.to_vec()).unwrap();
                    writeln!(out, "{} {}", name.trim_end(), salary).ok();
                    break;
                }
            }
        }
    }
}

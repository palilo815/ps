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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
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
    let n = sc.read::<usize>();
    let a = (0..5).map(|_| sc.read_vec::<usize>(n)).collect::<Vec<_>>();
    let mut ptrs = [(0, 1); 5];
    let mut score = vec![0; n + 1];
    let mut dead = vec![false; n + 2];
    for _ in 2..n {
        for (cow, &(f, s)) in a.iter().zip(ptrs.iter()) {
            score[cow[f]] += 2;
            score[cow[s]] += 1;
        }
        let mut best = 0;
        for (cow, &(f, s)) in a.iter().zip(ptrs.iter()) {
            if score[cow[f]] > score[best] {
                best = cow[f]
            }
            if score[cow[s]] > score[best] {
                best = cow[s]
            }
        }
        writeln!(out, "{}", best).ok();
        dead[best] = true;
        for (cow, (f, s)) in a.iter().zip(ptrs.iter_mut()) {
            score[cow[*f]] = 0;
            score[cow[*s]] = 0;
            if cow[*f] == best {
                *f = *s;
                *s += 1;
            }
            while dead[cow[*s]] {
                *s += 1;
            }
        }
    }
    for (cow, &(f, s)) in a.iter().zip(ptrs.iter()) {
        score[cow[f]] += 2;
        score[cow[s]] += 1;
    }
    if score[a[0][ptrs[0].0]] < score[a[0][ptrs[0].1]] {
        std::mem::swap(&mut ptrs[0].0, &mut ptrs[0].1);
    }
    writeln!(out, "{}\n{}", a[0][ptrs[0].0], a[0][ptrs[0].1]).ok();
}

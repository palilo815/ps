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
    let n = sc.read::<usize>();
    let t = sc.read::<usize>();
    let p = sc.read::<usize>() - 1;
    let stat = (0..n)
        .map(|_| (0..t).map(|_| sc.read::<char>() == '1').collect::<Vec<_>>())
        .collect::<Vec<_>>();
    let score = (0..t)
        .map(|i| stat.iter().fold(n as u32, |acc, s| acc - s[i] as u32))
        .collect::<Vec<_>>();
    let total = stat
        .into_iter()
        .map(|s| {
            s.into_iter().enumerate().fold(0, |acc, (i, ok)| {
                if ok {
                    acc + ((score[i] as u64) << 32) + 1
                } else {
                    acc
                }
            })
        })
        .collect::<Vec<_>>();
    let me = total[p];
    write!(out, "{} ", me >> 32).ok();
    write!(
        out,
        "{} ",
        total.iter().take(p).filter(|&&x| x >= me).count()
            + total.iter().skip(p).filter(|&&x| x > me).count()
            + 1
    )
    .ok();
}

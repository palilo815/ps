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
    let k = sc.read::<i32>();
    let moves = (0..n)
        .map(|_| (sc.read::<char>(), sc.read::<i32>()))
        .collect::<Vec<_>>();
    let mut coordis = Vec::with_capacity(1_000_000);
    const INF: i64 = 0x3f3f3f3f;
    moves.iter().fold((0, 0), |(mut pos, mut t), &(dir, step)| {
        let delta = match dir {
            'W' => -1,
            'E' => 1,
            'S' => -INF,
            _ => INF,
        };
        for _ in 0..step {
            pos += delta;
            t += 1;
            coordis.push((pos, t));
        }
        (pos, t)
    });
    coordis.sort_unstable();
    let parametric = |mut lo, mut hi| {
        let f = |mid| -> bool {
            coordis
                .iter()
                .fold((0, INF, INF), |(acc, prv_pos, prv_time), &(pos, time)| {
                    if prv_pos != pos {
                        (acc, pos, time)
                    } else if prv_time + mid > time {
                        (acc, pos, prv_time)
                    } else {
                        (acc + 1, pos, time)
                    }
                })
                .0
                >= k
        };
        // last true
        while lo != hi {
            let mid = hi - (hi - lo) / 2;
            if f(mid) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        lo
    };
    writeln!(out, "{}", parametric(-1, 999_999)).ok();
}

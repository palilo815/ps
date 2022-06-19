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

struct OneWayDSU {
    p: Vec<usize>,
}

impl OneWayDSU {
    fn new(n: usize) -> Self {
        Self {
            p: vec![usize::MAX; n],
        }
    }
    fn find(&mut self, mut i: usize) -> usize {
        while self.p[i] != usize::MAX {
            if self.p[self.p[i]] != usize::MAX {
                self.p[i] = self.p[self.p[i]];
            }
            i = self.p[i];
        }
        i
    }
    fn erase(&mut self, i: usize) {
        self.p[i] = i + 1;
    }
}

fn run<W: Write>(sc: &mut Scanner, out: &mut BufWriter<W>) {
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let o = sc.read::<usize>();
    let mut rooms = (0..n)
        .map(|_| (sc.read::<i32>(), sc.read::<i32>()))
        .collect::<Vec<_>>();
    let mut offers = (0..m)
        .map(|_| (sc.read::<i32>(), sc.read::<i32>()))
        .collect::<Vec<_>>();
    rooms.sort_unstable_by(|lhs, rhs| lhs.1.cmp(&rhs.1).then(lhs.0.cmp(&rhs.0)));
    offers.sort_unstable_by(|lhs, rhs| rhs.0.cmp(&lhs.0));
    let mut dsu = OneWayDSU::new(n + 1);
    let mut bills = vec![0; n.min(m)];
    let mut i = 0;
    for (v, d) in offers.into_iter() {
        let cheapest = rooms.partition_point(|it| it.1 < d);
        let room_id = dsu.find(cheapest);
        if room_id != n && v > rooms[room_id].0 {
            dsu.erase(room_id);
            bills[i] = v - rooms[room_id].0;
            i += 1;
        }
    }
    bills.select_nth_unstable_by(o - 1, |lhs, rhs| rhs.cmp(lhs));
    writeln!(
        out,
        "{}",
        bills.into_iter().take(o).fold(0, |acc, x| acc + x as i64)
    )
    .ok();
}

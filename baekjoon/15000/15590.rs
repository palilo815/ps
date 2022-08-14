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
    let m = sc.read::<usize>();
    let r = sc.read::<usize>();
    let mut cow = sc.read_vec::<u32>(n);
    let mut deal = (0..m)
        .map(|_| (sc.read::<u32>(), sc.read::<u32>()))
        .collect::<Vec<_>>();
    let mut rental = sc.read_vec::<u32>(r);
    cow.sort_unstable();
    deal.sort_unstable_by(|lhs, rhs| rhs.1.cmp(&lhs.1));
    rental.sort_unstable_by(|lhs, rhs| rhs.cmp(&lhs));
    rental.resize(n.min(r), 0);
    let mut acc = rental.iter().fold(0, |acc, &x| acc + x as u64);
    let mut milk = cow
        .iter()
        .skip(rental.len())
        .fold(0, |acc, &x| acc + x as u64);
    let mut i = 0;
    while i != m && milk != 0 {
        let amount = milk.min(deal[i].0.into());
        milk -= amount;
        acc += amount * deal[i].1 as u64;
        deal[i].0 -= amount as u32;
        if deal[i].0 == 0 {
            i += 1;
        }
    }
    let mut ans = acc;
    for (mut milk, fee) in cow.into_iter().zip(rental.into_iter()).rev() {
        acc -= fee as u64;
        while i != m && milk != 0 {
            let amount = milk.min(deal[i].0);
            milk -= amount;
            acc += amount as u64 * deal[i].1 as u64;
            deal[i].0 -= amount;
            if deal[i].0 == 0 {
                i += 1;
            }
        }
        ans = ans.max(acc);
    }
    writeln!(out, "{}", ans).ok();
}

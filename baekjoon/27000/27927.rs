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

use std::cmp::*;

#[derive(Eq, PartialEq)]
struct MinHeapNode(i32, usize);

impl Ord for MinHeapNode {
    fn cmp(&self, rhs: &Self) -> Ordering {
        rhs.0.cmp(&(self.0))
    }
}

impl PartialOrd for MinHeapNode {
    fn partial_cmp(&self, rhs: &Self) -> Option<Ordering> {
        Some(self.cmp(rhs))
    }
}

#[derive(Eq, PartialEq)]
struct MaxHeapNode(i32, usize);

impl Ord for MaxHeapNode {
    fn cmp(&self, rhs: &Self) -> Ordering {
        self.0.cmp(&(rhs.0))
    }
}

impl PartialOrd for MaxHeapNode {
    fn partial_cmp(&self, rhs: &Self) -> Option<Ordering> {
        Some(self.cmp(rhs))
    }
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let _ = sc.read::<u32>();
    let flowers = (0..n).map(|_| (sc.read::<i32>(), sc.read::<i32>() + 1)).collect::<Vec<_>>();
    let mut s_heap = std::collections::BinaryHeap::with_capacity(n);
    let mut e_heap = std::collections::BinaryHeap::with_capacity(n);
    let mut con = Vec::with_capacity(n);
    let mut best = 0;
    let mut l = 0;
    for r in 0..n {
        s_heap.push(MaxHeapNode(flowers[r].0, r));
        e_heap.push(MinHeapNode(flowers[r].1, r));
        loop {
            if s_heap.peek().unwrap().1 < l {
                s_heap.pop();
            } else if e_heap.peek().unwrap().1 < l {
                e_heap.pop();
            } else if s_heap.peek().unwrap().0 >= e_heap.peek().unwrap().0 {
                l += 1;
            } else {
                break;
            }
        }
        if best < r - l {
            best = r - l;
            con.clear();
            con.push((s_heap.peek().unwrap().0, e_heap.peek().unwrap().0));
        } else if best == r - l {
            con.push((s_heap.peek().unwrap().0, e_heap.peek().unwrap().0));
        }
    }
    con.sort_unstable_by(|l, r| l.0.cmp(&r.0));
    let cnt = con
        .into_iter()
        .fold((0, 0), |(acc, rmax), (s, e)| {
            (acc + 0.max(e - (s.max(rmax))), e.max(rmax))
        })
        .0;
    writeln!(out, "{} {}", best + 1, cnt).ok();
}

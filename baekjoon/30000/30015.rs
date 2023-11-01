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
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn partition<'a, A: 'a, I, F>(iter: I, mut pred: F) -> usize
where
    I: IntoIterator<Item = &'a mut A>,
    I::IntoIter: DoubleEndedIterator,
    F: FnMut(&A) -> bool,
{
    let mut split_index = 0;
    let mut iter = iter.into_iter();
    'main: while let Some(front) = iter.next() {
        if !pred(front) {
            loop {
                match iter.next_back() {
                    Some(back) => {
                        if pred(back) {
                            std::mem::swap(front, back);
                            break;
                        }
                    }
                    None => break 'main,
                }
            }
        }
        split_index += 1;
    }
    split_index
}

fn main() {
    let (mut sc, mut out) = unsafe {
        static mut S: String = String::new();
        stdin().read_to_string(&mut S).unwrap();
        (Scanner::new(&S), BufWriter::new(stdout().lock()))
    };
    let n = sc.read::<usize>();
    let k = sc.read::<usize>();
    let mut a = sc.read_vec::<u32>(n);
    for i in (0..20).rev() {
        let mask = 1 << i;
        let p = partition(&mut a, |x| x & mask != 0);
        if p >= k {
            a.truncate(p);
        }
    }
    writeln!(
        out,
        "{}",
        a.into_iter().take(k).fold(u32::MAX, std::ops::BitAnd::bitand)
    )
    .ok();
}

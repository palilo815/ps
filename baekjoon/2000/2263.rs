use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
    fn read_vec<T: std::str::FromStr>(&mut self, len: usize) -> Vec<T> {
        (0..len).map(|_| self.read()).collect()
    }
}

fn run(offset: usize, in_ord: &[i32], post_ord: &[i32], index: &[usize], bw: &mut BufWriter<StdoutLock<'static>>) {
    if in_ord.is_empty() {
        return;
    }
    let u = *post_ord.last().unwrap();
    write!(bw, "{u} ").ok();
    let i = index[u as usize - 1] - offset;
    run(offset, &in_ord[..i], &post_ord[..i], index, bw);
    run(
        offset + i + 1,
        &in_ord[i + 1..],
        &post_ord[i..post_ord.len() - 1],
        index,
        bw,
    );
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let in_ord = sc.read_vec::<i32>(n);
    let post_ord = sc.read_vec::<i32>(n);
    let mut index = vec![0; n];
    for (i, &x) in in_ord.iter().enumerate() {
        index[x as usize - 1] = i;
    }
    run(0, &in_ord, &post_ord, &index, &mut bw);
}

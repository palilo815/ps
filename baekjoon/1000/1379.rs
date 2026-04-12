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
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    let n = sc.read::<usize>();
    let mut st = vec![(0, 0); n];
    let mut ed = vec![(0, 0); n];
    for i in 0..n {
        let id = sc.read::<u32>() - 1;
        st[i] = (sc.read::<u32>(), id);
        ed[i] = (sc.read::<u32>(), id);
    }
    st.sort_unstable_by_key(|x| x.0);
    ed.sort_unstable_by_key(|x| x.0);
    let mut ans = vec![-1; n];
    let mut room_buffer = vec![];
    let mut room_count = 0;
    let mut i = 0;
    let mut j = 0;
    while i != n {
        if st[i].0 < ed[j].0 {
            let id = st[i].1 as usize;
            if let Some(room) = room_buffer.pop() {
                ans[id] = room;
            } else {
                room_count += 1;
                ans[id] = room_count;
            }
            i += 1;
        } else {
            let id = ed[j].1 as usize;
            room_buffer.push(ans[id]);
            j += 1;
        }
    }
    writeln!(bw, "{room_count}").ok();
    for x in ans {
        writeln!(bw, "{x}").ok();
    }
}

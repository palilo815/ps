use std::io::Write;

#[allow(dead_code)]
mod scanner {
    use std::str::FromStr;
    pub struct Scanner<'a> {
        it: std::str::SplitWhitespace<'a>,
    }
    impl<'a> Scanner<'a> {
        pub fn new(s: &'a str) -> Scanner<'a> {
            Scanner {
                it: s.split_whitespace(),
            }
        }
        pub fn next<T: FromStr>(&mut self) -> T {
            self.it.next().unwrap().parse::<T>().ok().unwrap()
        }
        pub fn next_bytes(&mut self) -> Vec<u8> {
            self.it.next().unwrap().bytes().collect()
        }
        pub fn next_chars(&mut self) -> Vec<char> {
            self.it.next().unwrap().chars().collect()
        }
        pub fn next_vec<T: FromStr>(&mut self, len: usize) -> Vec<T> {
            (0..len).map(|_| self.next()).collect()
        }
    }
}

fn main() {
    use std::io::Read;
    let mut s = String::new();
    std::io::stdin().read_to_string(&mut s).unwrap();
    let mut sc = scanner::Scanner::new(&s);
    let out = std::io::stdout();
    let mut out = std::io::BufWriter::new(out.lock());
    run(&mut sc, &mut out);
}

fn run<W: Write>(sc: &mut scanner::Scanner, out: &mut std::io::BufWriter<W>) {
    let n = sc.next::<usize>();
    let mut st = vec![(0, 0); n];
    let mut ed = vec![(0, 0); n];
    for i in 0..n {
        let id = sc.next::<u32>() - 1;
        st[i] = (sc.next::<u32>(), id);
        ed[i] = (sc.next::<u32>(), id);
    }
    st.sort_unstable_by_key(|x| x.0);
    ed.sort_unstable_by_key(|x| x.0);
    let mut ans = vec![-1; n];
    let mut empty_room = vec![];
    let mut room_num = 0;
    let mut i = 0;
    let mut j = 0;
    while i != n {
        if st[i].0 < ed[j].0 {
            let id = st[i].1 as usize;
            if let Some(room) = empty_room.pop() {
                ans[id] = room;
            } else {
                room_num += 1;
                ans[id] = room_num;
            }
            i += 1;
        } else {
            let id = ed[j].1 as usize;
            empty_room.push(ans[id]);
            j += 1;
        }
    }
    writeln!(out, "{}", room_num).ok();
    for x in ans {
        writeln!(out, "{}", x).ok();
    }
}

use std::io::*;

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut it = s.split('\n');
    let mut bw = BufWriter::new(stdout().lock());
    let t = it.next().unwrap().parse::<usize>().unwrap();
    for _ in 0..t {
        let mut ans = it.next().unwrap().split_ascii_whitespace().collect::<Vec<_>>();
        loop {
            let hint = it.next().unwrap();
            let ban = hint.split_ascii_whitespace().last().unwrap();
            if ban == "say?" {
                break;
            }
            ans.retain(|&s| s != ban);
        }
        for s in ans {
            write!(bw, "{s} ").ok();
        }
        writeln!(bw).ok();
    }
}

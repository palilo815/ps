use std::io::*;

fn main() {
    let mut bw = BufWriter::new(stdout().lock());
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut it = s.split('\n');
    const N: usize = 200;
    let mut music = vec![String::new(); N];
    for t in 1.. {
        let n = it.next().unwrap().parse::<usize>().unwrap();
        if n == 0 {
            break;
        }
        let music = &mut music[..n];
        music.fill_with(|| it.next().unwrap().to_string());
        music.sort_unstable();
        writeln!(bw, "{t}").ok();
        for x in music {
            writeln!(bw, "{x}").ok();
        }
    }
}

use std::io::*;

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut it = s.split('\n');
    let mut bw = BufWriter::new(stdout().lock());
    const CODE: [char; 26] = [
        'y', 'h', 'e', 's', 'o', 'c', 'v', 'x', 'd', 'u', 'i', 'g', 'l', 'b', 'k', 'r', 'z', 't', 'n', 'w', 'j', 'p',
        'f', 'm', 'a', 'q',
    ];
    const A: usize = 'a' as usize;
    let t = it.next().unwrap().parse::<usize>().unwrap();
    for t in 1..=t {
        write!(bw, "Case #{t}: ").ok();
        for c in it.next().unwrap().chars() {
            let c = match c {
                ' ' => ' ',
                _ => CODE[c as usize - A],
            };
            write!(bw, "{c}").ok();
        }
        writeln!(bw).ok();
    }
}

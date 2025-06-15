use std::io::*;

fn main() {
    let mut bw = BufWriter::new(stdout().lock());
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut it = s.split('\n');
    let mut stack = vec![];
    loop {
        let s = it.next().unwrap();
        if s == "#" {
            break;
        }
        stack.clear();
        let ok = s.bytes().all(|x| match x {
            b'(' | b'{' | b'[' => {
                stack.push(x);
                true
            }
            b')' => stack.pop().is_some_and(|y| y == b'('),
            b'}' => stack.pop().is_some_and(|y| y == b'{'),
            b']' => stack.pop().is_some_and(|y| y == b'['),
            _ => true,
        }) && stack.is_empty();
        writeln!(bw, "{}", if ok { "Legal" } else { "Illegal" }).ok();
    }
}

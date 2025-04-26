use std::io::*;

fn main() {
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    s.truncate(s.trim_end().len());
    let mut stack = Vec::with_capacity(s.len());
    let mut ans = Vec::with_capacity(s.len());
    for c in s.bytes() {
        match c {
            b'(' => stack.push(c),
            b')' => {
                while stack.last().is_some_and(|&c| c != b'(') {
                    ans.push(stack.pop().unwrap());
                }
                stack.pop();
            }
            b'+' | b'-' => {
                while stack.last().is_some_and(|&c| c != b'(') {
                    ans.push(stack.pop().unwrap());
                }
                stack.push(c);
            }
            b'*' | b'/' => {
                while stack.last().is_some_and(|&c| c == b'*' || c == b'/') {
                    ans.push(stack.pop().unwrap());
                }
                stack.push(c);
            }
            _ => ans.push(c),
        }
    }
    ans.extend(stack.into_iter().rev());
    println!("{}", String::from_utf8(ans).unwrap());
}

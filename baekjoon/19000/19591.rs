use std::io::*;

fn main() {
    let mut bw = BufWriter::new(stdout().lock());
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    let mut it = s.trim_end().chars().peekable();
    let mut nums = std::collections::VecDeque::new();
    let mut ops = std::collections::VecDeque::new();
    let mut num = 0;
    let mut neg = false;
    if it.peek().is_some_and(|&c| c == '-') {
        neg = true;
        it.next();
    }
    for c in it {
        if c.is_ascii_digit() {
            num = num * 10 + c.to_digit(10).unwrap() as i64;
        } else {
            nums.push_back(if neg { -num } else { num });
            ops.push_back(c);
            num = 0;
            neg = false;
        }
    }
    nums.push_back(if neg { -num } else { num });
    let calc = |x: i64, y: i64, op: char| -> i64 {
        match op {
            '+' => x + y,
            '-' => x - y,
            '*' => x * y,
            _ => x / y,
        }
    };
    while !ops.is_empty() {
        let op1 = *ops.front().unwrap() == '*' || *ops.front().unwrap() == '/';
        let op2 = *ops.back().unwrap() == '*' || *ops.back().unwrap() == '/';
        let do_first = if op1 == op2 {
            let r1 = calc(nums[0], nums[1], ops[0]);
            let r2 = calc(nums[nums.len() - 2], nums[nums.len() - 1], ops[ops.len() - 1]);
            r1 >= r2
        } else {
            op1
        };
        if do_first {
            let x = nums.pop_front().unwrap();
            let y = nums.pop_front().unwrap();
            let op = ops.pop_front().unwrap();
            nums.push_front(calc(x, y, op));
        } else {
            let y = nums.pop_back().unwrap();
            let x = nums.pop_back().unwrap();
            let op = ops.pop_back().unwrap();
            nums.push_back(calc(x, y, op));
        }
    }
    writeln!(bw, "{}", nums[0]).ok();
}

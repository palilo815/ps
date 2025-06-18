use std::io::*;

#[derive(PartialEq)]
struct Clock {
    hour: u32,
    minute: u32,
    second: u32,
}

impl Clock {
    fn new(s: &str) -> Self {
        let s = s.as_bytes();
        let hour = ((s[0] - b'0') * 10 + (s[1] - b'0')) as u32;
        let minute = ((s[3] - b'0') * 10 + (s[4] - b'0')) as u32;
        let second = ((s[6] - b'0') * 10 + (s[7] - b'0')) as u32;
        Self { hour, minute, second }
    }
    fn div_by_3(&self) -> bool {
        (self.hour * 10000 + self.minute * 100 + self.second) % 3 == 0
    }
    fn increment(&mut self) {
        match self.second {
            59 => {
                self.second = 0;
                match self.minute {
                    59 => {
                        self.minute = 0;
                        self.hour = (self.hour + 1) % 24;
                    }
                    _ => self.minute += 1,
                }
            }
            _ => self.second += 1,
        }
    }
}

fn main() {
    let mut bw = BufWriter::new(stdout().lock());
    let mut s = String::new();
    stdin().read_to_string(&mut s).ok();
    for s in s.split_terminator('\n') {
        let (a, b) = s.split_once(' ').unwrap();
        let mut a = Clock::new(a);
        let b = Clock::new(b);
        let mut ans = 0;
        loop {
            ans += a.div_by_3() as i32;
            if a == b {
                break;
            }
            a.increment();
        }
        writeln!(bw, "{ans}").ok();
    }
}

/**
* @date     2022-01-31
* @author   palilo
* @test     stress test
*/
struct MaxStack<T> {
    stack: Vec<T>,
    maximum: T,
}

impl<T> MaxStack<T>
where
    T: std::default::Default
        + std::marker::Copy
        + std::cmp::Ord
        + std::ops::Shl<u32, Output = T>
        + std::ops::Sub<T, Output = T>,
{
    fn new() -> Self {
        Self {
            stack: vec![],
            maximum: Default::default(),
        }
    }
    fn is_empty(&self) -> bool {
        self.stack.is_empty()
    }
    fn get_max(&self) -> Option<T> {
        if self.stack.is_empty() {
            None
        } else {
            Some(self.maximum)
        }
    }
    fn top(&self) -> Option<T> {
        self.stack.last().map(|val| self.maximum.min(*val))
    }
    fn push(&mut self, x: T) {
        if self.stack.is_empty() {
            self.maximum = x;
            self.stack.push(x);
        } else if x > self.maximum {
            self.stack.push((x << 1) - self.maximum);
            self.maximum = x;
        } else {
            self.stack.push(x);
        }
    }
    fn pop(&mut self) -> Option<T> {
        self.stack.pop().map(|mut val| {
            if val > self.maximum {
                let real = self.maximum;
                self.maximum = (self.maximum << 1) - val;
                val = real;
            }
            val
        })
    }
}

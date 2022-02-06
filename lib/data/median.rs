/**
* @date     2022-02-06
* @author   palilo
* @brief    implement running-median algorithm
* @test     http://boj.kr/3b5ed426e4394c25bcdee8e34a444060
*/
struct RunningMedian<T> {
    left: std::collections::BinaryHeap<T>,
    right: std::collections::BinaryHeap<std::cmp::Reverse<T>>,
}

#[allow(dead_code)]
impl<T> RunningMedian<T>
where
    T: std::cmp::Ord + std::marker::Copy,
{
    fn new() -> Self {
        Self {
            left: Default::default(),
            right: Default::default(),
        }
    }
    fn with_capacity(n: usize) -> Self {
        Self {
            left: std::collections::BinaryHeap::with_capacity((n + 1) >> 1),
            right: std::collections::BinaryHeap::with_capacity((n + 1) >> 1),
        }
    }
    fn clear(&mut self) {
        self.left.clear();
        self.right.clear();
    }
    fn push(&mut self, mut x: T) {
        if self.left.len() == self.right.len() {
            if let Some(mut right_min) = self.right.peek_mut() {
                if x > right_min.0 {
                    std::mem::swap(&mut x, &mut right_min.0);
                }
            }
            self.left.push(x);
        } else {
            let mut left_max = self.left.peek_mut().unwrap();
            if x < *left_max {
                std::mem::swap(&mut x, &mut left_max);
            }
            self.right.push(std::cmp::Reverse(x));
        }
    }
    fn get_median(&mut self) -> Option<&T> {
        self.left.peek()
    }
}

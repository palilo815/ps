fn lis<T: Copy + PartialOrd>(a: &[T]) -> usize {
    let mut dp = Vec::with_capacity(a.len());
    for x in a.iter() {
        let i = dp.partition_point(|item| item < x);
        if i == dp.len() {
            dp.push(*x);
        } else {
            dp[i] = *x;
        }
    }
    dp.len()
}

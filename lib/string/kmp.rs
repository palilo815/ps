mod kmp {
    use std::cmp::PartialEq;

    pub fn positions<T: PartialEq>(s: &[T], k: &[T]) -> Vec<usize> {
        let fail = lps(k);
        let mut res = vec![];
        let mut j = 0;
        for i in 0..s.len() {
            while j != 0 && s[i] != k[j] {
                j = fail[j - 1];
            }
            if s[i] == k[j] {
                j += 1;
                if j == k.len() {
                    res.push(i + 1 - k.len());
                    j = *fail.last().unwrap();
                }
            }
        }
        res
    }

    fn lps<T: PartialEq>(s: &[T]) -> Vec<usize> {
        let mut r = vec![0; s.len()];
        let mut j = 0;
        for i in 1..s.len() {
            while j != 0 && s[i] != s[j] {
                j = r[j - 1];
            }
            if s[i] == s[j] {
                j += 1;
                r[i] = j;
            }
        }
        r
    }
}

use std::io::*;

struct Scanner {
    it: std::str::SplitAsciiWhitespace<'static>,
}

impl Scanner {
    fn new() -> Self {
        let mut s = String::new();
        stdin().read_to_string(&mut s).ok();
        Self { it: s.leak().split_ascii_whitespace() }
    }
    fn read<T: std::str::FromStr>(&mut self) -> T {
        self.it.next().unwrap().parse::<T>().ok().unwrap()
    }
}

#[derive(Clone, Copy, Debug)]
struct Matrix<const N: usize, const M: usize, T> {
    data: [[T; M]; N],
}

impl<const N: usize, const M: usize, T> Matrix<N, M, T>
where
    T: std::ops::Add<Output = T> + Copy + Default,
{
    fn add(&self, other: &Self) -> Self {
        let mut result = Self { data: [[T::default(); M]; N] };
        for i in 0..N {
            for j in 0..M {
                result.data[i][j] = self.data[i][j] + other.data[i][j];
            }
        }
        result
    }
}

impl<const N: usize, const K: usize, const M: usize, T> std::ops::Mul<Matrix<K, M, T>> for Matrix<N, K, T>
where
    T: std::ops::Add<Output = T> + std::ops::Mul<Output = T> + Copy + Default,
{
    type Output = Matrix<N, M, T>;
    fn mul(self, rhs: Matrix<K, M, T>) -> Self::Output {
        let mut result = Matrix { data: [[T::default(); M]; N] };
        for i in 0..N {
            for j in 0..M {
                let mut sum = T::default();
                for k in 0..K {
                    sum = sum + self.data[i][k] * rhs.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        result
    }
}

impl<const N: usize, const M: usize, T> Matrix<N, M, T> {
    fn new(data: [[T; M]; N]) -> Self {
        Self { data }
    }
}

fn main() {
    let mut sc = Scanner::new();
    let mut bw = BufWriter::new(stdout().lock());
    const MOD: i64 = 1_000_000_000;
    let n = sc.read::<isize>();
    if n == 0 {
        writeln!(bw, "0\n0").ok();
        return;
    }
    let mut mat = Matrix::new(if n < 0 { [[-1, 1], [1, 0]] } else { [[1, 1], [1, 0]] });
    let mut result = Matrix::new([[1, 0], [0, 1]]);
    let mut n = n.abs();
    while n != 0 {
        if n & 1 == 1 {
            result = result * mat;
            result.data.iter_mut().flatten().for_each(|x| *x %= MOD);
        }
        mat = mat * mat;
        mat.data.iter_mut().flatten().for_each(|x| *x %= MOD);
        n >>= 1;
    }
    let res = result * Matrix::new([[0], [1]]);
    let res = res.data[0][0];
    let sign = match res.cmp(&0) {
        std::cmp::Ordering::Less => -1,
        std::cmp::Ordering::Greater => 1,
        std::cmp::Ordering::Equal => 0,
    };
    let res = res.abs();
    writeln!(bw, "{sign}\n{res}").ok();
}

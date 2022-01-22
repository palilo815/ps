/**
* @date     2022-01-22
* @author   palilo
* @brief    sparse table 
*           a data structure that can answer overlap-friendly operation in O(1) time
*/
pub struct SparseTable<T, F> {
    size: usize,
    table: Vec<Vec<T>>,
    op: F,
}

impl<T, F> SparseTable<T, F>
where
    F: Fn(&T, &T) -> T,
{
    pub fn new(a: Vec<T>, op: F) -> Self {
        let size = a.len();
        let mut table =
            Vec::with_capacity(8 * std::mem::size_of::<usize>() - size.leading_zeros() as usize);
        table.push(a);
        let mut k = 1;
        for i in 1..table.capacity() {
            table.push(
                (0..=(size - (k << 1)))
                    .map(|j| op(&table[i - 1][j], &table[i - 1][j + k]))
                    .collect::<Vec<_>>(),
            );
            k <<= 1;
        }
        SparseTable { size, table, op }
    }
    pub fn product(&self, l: usize, r: usize) -> T {
        assert!(l < r && r <= self.size);
        let k = (8 * std::mem::size_of::<usize>() - 1) ^ (r - l).leading_zeros() as usize;
        (self.op)(&self.table[k][l], &self.table[k][r - (1 << k)])
    }
}

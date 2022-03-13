struct SCC {
    size: usize,
    g: Vec<Vec<usize>>,
}

impl SCC {
    fn new(size: usize) -> Self {
        Self {
            size,
            g: vec![vec![]; size],
        }
    }
    fn add_edge(&mut self, u: usize, v: usize) {
        assert!(u < self.size && v < self.size);
        self.g[u].push(v);
    }
    fn run(&self) -> Vec<i32> {
        let mut id = vec![-1; self.size];
        let mut disc = vec![-1; self.size];
        let mut stk = vec![];
        for i in 0..self.size {
            if disc[i] == -1 {
                self.dfs(i, &mut disc, &mut stk, &mut id);
            }
        }
        assert!(stk.is_empty());
        id
    }
    fn dfs(&self, u: usize, disc: &mut [i32], stk: &mut Vec<usize>, id: &mut [i32]) -> i32 {
        static mut T: i32 = 0;
        static mut C: i32 = 0;
        unsafe {
            disc[u] = T;
            T += 1;
        }
        stk.push(u);
        let mut lo = disc[u];
        for &v in self.g[u].iter() {
            if disc[v] == -1 {
                lo = lo.min(self.dfs(v, disc, stk, id));
            } else {
                lo = lo.min(disc[v]);
            }
        }
        if lo == disc[u] {
            unsafe {
                loop {
                    let x = stk.pop().unwrap();
                    disc[x] = i32::MAX;
                    id[x] = C;
                    if x == u {
                        break;
                    }
                }
                C += 1;
            }
        }
        lo
    }
}

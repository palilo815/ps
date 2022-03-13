fn hld(adj: &mut Vec<Vec<usize>>, root: usize) -> (Vec<usize>, Vec<usize>, Vec<u32>, Vec<u32>) {
    let n = adj.len();
    let mut stk = Vec::with_capacity(n);
    let mut par = vec![0; n];
    stk.push(root);
    let dfs_order = (0..n)
        .map(|_| {
            let u = stk.pop().unwrap();
            if let Some(p) = adj[u].iter().position(|&v| v == par[u]) {
                adj[u].swap_remove(p);
            }
            for &v in adj[u].iter() {
                par[v] = u;
                stk.push(v);
            }
            u
        })
        .collect::<Vec<_>>();
    let mut sz = vec![0; n];
    for &u in dfs_order.iter().rev() {
        sz[u] = adj[u].iter().map(|&v| sz[v]).sum::<u32>() + 1;
        if let Some((heavy, _)) = adj[u].iter().enumerate().max_by_key(|(_, x)| sz[**x]) {
            let last = adj[u].len() - 1;
            adj[u].swap(heavy, last);
        }
    }
    let mut top = vec![0; n];
    let mut tin = vec![0; n];
    stk.push(root);
    for t in 0..n as u32 {
        let u = stk.pop().unwrap();
        tin[u] = t;
        adj[u].iter().for_each(|&v| top[v] = v);
        stk.extend_from_slice(&adj[u]);
        if !adj[u].is_empty() {
            top[*stk.last().unwrap()] = top[u];
        }
    }
    (par, top, tin, sz)
}


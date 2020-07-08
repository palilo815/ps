ll fen1[max_N], fen2[max_N];

void update(ll fenwick[], int i, int v) {
    for (; i <= N; i += i & -i)
        fenwick[i] += v;
}
void update_range(int l, int r) {
    update(fen1, l, 1), update(fen1, r + 1, -1);
    update(fen2, l, l - 1), update(fen2, r + 1, -r);
}
ll read(ll fenwick[], int i) {
    ll ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
ll read_range(int l, int r) {
    return read(fen1, r) * r - read(fen2, r) -
           read(fen1, l - 1) * (l - 1) + read(fen2, l - 1);
}
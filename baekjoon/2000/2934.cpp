#include <bits/stdc++.h>
using namespace std;

const int M = 1e5 + 1;

int fenwick[M];

void update(int i, int v) {
    for (; i < M; i += i & -i)
        fenwick[i] += v;
}
int read(int i) {
    int ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0, l, r, L, R; i < N; ++i) {
        cin >> l >> r;
        L = read(l), R = read(r);
        cout << L + R << '\n';
        update(l, -L), update(l + 1, L + 1);
        update(r, -R - 1), update(r + 1, R);
    }
    return 0;
}
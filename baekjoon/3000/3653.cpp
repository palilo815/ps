#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;
const int max_M = 100000;

int N, M;
int pos[max_N + 1];
int fenwick[max_N + max_M + 1];

int read(int idx)
{
    int ret = 0;
    while (idx) {
        ret += fenwick[idx];
        idx -= (idx & -idx);
    }
    return ret;
}
void update(int idx, int val)
{
    while (idx <= N + M) {
        fenwick[idx] += val;
        idx += (idx & -idx);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        cin >> N >> M;
        memset(fenwick, 0, sizeof(fenwick));
        for (int i = 1; i <= N; ++i)
            pos[i] = M + i;
        for (int i = M + 1; i <= M + N; ++i)
            update(i, 1);

        for (int i = 0; i < M; ++i) {
            int x; cin >> x;
            int idx = pos[x];
            update(idx, -1);
            cout << read(idx) << ' ';
            update(M - i, 1);
            pos[x] = M - i;
        }
        cout << '\n';
    }
    return 0;
}
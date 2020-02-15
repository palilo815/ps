#include <bits/stdc++.h>
using namespace std;

const int max_N = 500000;
const int max_idx = 1000000;

int N;
int pos[max_idx + 1];
int fenwick[max_N + 1];

int read(int idx)
{
    int ret = 0;
    while (idx) {
        ret += fenwick[idx];
        idx -= (idx & -idx);
    }
    return ret;
}
void update(int idx)
{
    while (idx <= N) {
        --fenwick[idx];
        idx += (idx & -idx);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    for (int i = 1; i <= N; ++i) {
        int idx; cin >> idx;
        pos[idx] = i;
    }
    for (int i = 1; i <= N; ++i)
        fenwick[i] = i & -i;

    long long ans = 0;
    for (int i = 0; i < N; ++i) {
        int x; cin >> x;
        int idx = pos[x];
        update(idx);
        ans += read(idx);
    }
    cout << ans;
    return 0;
}
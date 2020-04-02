#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    int ans = M + 1;
    
    bool check[10];
    vector<vector<int>> vt(M);

    for (int i = 0; i < M; ++i) {
        int cnt; cin >> cnt;
        while (cnt--) {
            int idx; cin >> idx;
            vt[i].emplace_back(idx - 1);
        }
    }

    for (int mask = 1; mask < (1 << M); ++mask) {
        if (__builtin_popcount(mask) >= ans) continue;
        memset(check, 0, N);
        for (int i = 0; i < M; ++i) if (mask & (1 << i))
            for (int x : vt[i]) check[x] = true;

        bool flag = true;
        for (int i = 0; i < N; ++i)
            if (!check[i]) {
                flag = false;
                break;
            }
        if (flag) ans = __builtin_popcount(mask);
    }
    cout << (ans == M + 1 ? -1 : ans);
    return 0;
}
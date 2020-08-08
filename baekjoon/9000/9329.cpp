#include <bits/stdc++.h>
using namespace std;

const int mxN = 10;
const int mxM = 31;

vector<int> need[mxN];
int prize[mxN], sticker[mxM];

void solve() {
    int N, M; cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        int k; cin >> k;
        need[i] = vector<int>(k);
        for (int& x : need[i]) cin >> x;
        cin >> prize[i];
    }
    for (int i = 1; i <= M; ++i)
        cin >> sticker[i];

    int ans = 0;
    for (int i = 0; i < N; ++i)
        ans += prize[i] * sticker[*min_element(need[i].begin(), need[i].end(), [&](int& a, int& b) {
        return sticker[a] < sticker[b];
    })];
    cout << ans << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}
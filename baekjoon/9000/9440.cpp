#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N;
    for (cin >> N; N; cin >> N) {
        vector<int> vt;
        int zero = 0, ans = 0;
        for (int i = 0, x; i < N; ++i) {
            cin >> x;
            x ? vt.emplace_back(x) : ++zero;
        }
        sort(vt.begin(), vt.end(), greater<int>());

        vt.insert(vt.end() - 2, zero, 0);
        for (int i = 0, b = 1; i < N; i & 1 ? b *= 10, ++i : ++i)
            ans += vt[i] * b;
        cout << ans << '\n';
    }
    return 0;
}
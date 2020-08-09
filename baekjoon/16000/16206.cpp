#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    int ans = 0, tmp = 0;
    vector<int> cake;
    for (int x; N--;) {
        cin >> x;
        if (x == 10) ++ans;
        else x % 10 ? (tmp += x / 10) : cake.emplace_back(x);
    }

    sort(cake.begin(), cake.end());
    for (auto& x : cake) {
        if (x / 10 - 1 > M) ans += M, M = 0;
        else ans += x / 10, M -= x / 10 - 1;
        if (!M) break;
    }
    cout << ans + min(M, tmp);
    return 0;
}
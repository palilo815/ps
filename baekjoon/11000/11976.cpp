#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    int ans = 0, pos[7] {};
    for (int i = 1, x, s = 0; i <= N; ++i) {
        cin >> x;
        if (!pos[s]) pos[s] = i;
        s = (s + x) % 7;
        if (pos[s]) ans = max(ans, i - pos[s] + 1);
    }
    cout << ans;
    return 0;
}
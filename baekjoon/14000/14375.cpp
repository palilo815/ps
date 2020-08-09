#include <bits/stdc++.h>
using namespace std;

char s[16];

void solve() {
    cin >> s;
    deque<char> dq;
    dq.emplace_back(s[0]);

    for (int i = 1; s[i]; ++i)
        s[i] < dq.front() ? dq.emplace_back(s[i]) : dq.emplace_front(s[i]);

    for (auto& c : dq) cout << c;
    cout << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    for (int i = 1; i <= T; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
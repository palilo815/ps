#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N; cin >> N;
    char c; cin >> c;

    deque<char> dq;
    dq.emplace_back(c);

    while (--N) {
        cin >> c;
        c > dq.front() ? dq.emplace_back(c) : dq.emplace_front(c);
    }
    for (char& c : dq) cout << c;
    cout << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

void solve() {
    priority_queue<int, vector<int>, greater<int>> pq;
    char s[7];

    int Q, K; cin >> Q >> K;
    for (int x, sum = 0; Q; --Q) {
        cin >> s;
        if (s[0] == 'i') {
            cin >> x;
            pq.emplace(x);
            sum ^= x;
            if (pq.size() == K + 1) {
                sum ^= pq.top();
                pq.pop();
            }
        }
        else cout << sum << '\n';
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    priority_queue<int> pq;
    int N; cin >> N;
    for (int x; N--;) {
        cin >> x;
        pq.emplace(x);
    }

    int ans = 0;
    while (pq.size() ^ 1) {
        int x = pq.top(); pq.pop();
        int y = pq.top(); pq.pop();
        ans += x * y;
        pq.emplace(x + y);
    }
    cout << ans;
    return 0;
}
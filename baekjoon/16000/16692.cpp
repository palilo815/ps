#include <bits/stdc++.h>
using namespace std;
using p = pair<int, int>;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;

    priority_queue<p, vector<p>, greater<p>> pq;
    for (int i = 1; i <= N; ++i)
        pq.emplace(0, i);

    for (int i = 0, t, num; i < M; ++i) {
        cin >> t;
        t += pq.top().first;
        num = pq.top().second;

        pq.pop();
        pq.emplace(t, num);

        cout << num << ' ';
    }
    return 0;
}
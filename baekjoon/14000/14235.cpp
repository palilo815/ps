#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    priority_queue<int> pq;
    int N; cin >> N;
    for (int M; N; --N) {
        cin >> M;
        if (M)
            for (int x; M; --M) {
                cin >> x;
                pq.emplace(x);
            }
        else {
            if (pq.empty()) cout << -1;
            else {
                cout << pq.top(); pq.pop();
            }
            cout << '\n';
        }
    }
    return 0;
}
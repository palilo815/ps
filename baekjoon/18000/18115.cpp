#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e6;

char a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    deque<int> dq;

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    for (int x = 1, i = N - 1; ~i; --i, ++x) {
        switch (a[i]) {
        case '1': dq.emplace_front(x); break;
        case '3': dq.emplace_back(x); break;
        default:
            int y = dq.front(); dq.pop_front();
            dq.emplace_front(x);
            dq.emplace_front(y);
        }
    }

    for (int& x : dq)
        cout << x << ' ';
    return 0;
}
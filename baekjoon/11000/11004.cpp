#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e6;

int a[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, K;
    cin >> N >> K;
    --K;

    for (int i = 0; i < N; ++i)
        cin >> a[i];

    nth_element(a, a + K, a + N);
    cout << a[K];
}
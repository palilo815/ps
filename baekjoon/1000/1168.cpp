#include <bits/stdc++.h>
using namespace std;

const int sgN = 131072;

int bit[sgN + 1];

int query(int i) {
    int ret = 0;
    for (; i; i -= i & -i)
        ret += bit[i];
    return ret;
}
int kill(int k) {
    int s = 0;
    for (int len = sgN >> 1; len; len >>= 1)
        bit[s | len] < k ? (k -= bit[s |= len]) : --bit[s | len];
    return s + 1;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, K;
    cin >> N >> K;

    for (int i = 1; i <= N; ++i)
        for (int j = i; j <= sgN; j += j & -j)
            ++bit[j];

    for (int i = K; i <= sgN; i += i & -i)
        --bit[i];

    int i = K;
    cout << '<' << i;
    for (int x; --N; cout << ", " << i) {
        x = query(i - 1);
        i = kill(N - x < K ? (K - N + x) % N ? (K - N + x) % N : N : x + K);
    }
    cout << '>';
}
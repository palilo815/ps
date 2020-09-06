#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 1e3;

string a[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int K, N; cin >> K >> N;
    loop(i, K) cin >> a[i];

    string s = *max_element(a, a + K, [&](auto & a, auto & b) {
        if (a.size() ^ b.size()) return a.size() < b.size();
        loop(i, a.size()) if (a[i] ^ b[i])
            return a[i] < b[i];
        return false;
    });

    for (int i = K; i < N; ++i)
        a[i] = s;
    sort(a, a + N, [&](auto & a, auto & b) {
        auto ab = a + b, ba = b + a;
        return ab > ba;
    });

    loop(i, N) cout << a[i];
    return 0;
}
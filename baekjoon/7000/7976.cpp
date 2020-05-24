#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000000;

int cnt[max_N][2];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K; cin >> N >> K;
    loop(i, N) {
        int x; cin >> x;
        ++cnt[i % K][x & 1];
    }

    int odd = 0x3f3f3f3f, even = 0;
    loop(i, K) {
        int O = min(odd + cnt[i][1], even + cnt[i][0]);
        int E = min(even + cnt[i][1], odd + cnt[i][0]);
        odd = O, even = E;
    }
    cout << even;
    return 0;
}
#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 5e3;

bool a[mx], flip[mx + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) {
        char x; cin >> x;
        a[i] = x == 'F';
    }

    int M = INT_MAX, K = -1;
    loop(k, N) {
        memset(flip, 0, N);
        bool f = false;
        int cnt = 0;

        loop(i, N - k) if (a[i] == (f ^= flip[i])) {
            ++cnt;
            f = !f;
            flip[i + k + 1] = true;
        }
        for (int i = N - k; i < N; ++i)
            if (a[i] == (f ^= flip[i])) {
                cnt = INT_MAX;
                break;
            }
        if (cnt < M)
            M = cnt, K = k + 1;
    }
    cout << K << ' ' << M;
    return 0;
}
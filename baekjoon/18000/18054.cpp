#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 50;

int len, a[mxN << 1];
char s[251];

bool same(int k) {
    loop(i, k) for (int j = i + k; j < len; j += k)
        if (s[j] ^ s[i])
            return false;
    return true;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N << 1) {
        cin >> s;
        len = strlen(s);

        for (int j = 1; j < len; ++j)
            if (len % j == 0 && same(j)) {
                a[i] = j;
                break;
            }
        if (!a[i]) a[i] = len;
    }

    sort(a, a + N);
    sort(a + N, a + N + N);

    int ans = 0;
    loop(i, N) ans += (a[i] - a[i + N]) * (a[i] - a[i + N]);
    cout << ans;
    return 0;
}
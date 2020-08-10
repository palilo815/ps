#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 2e3;

char s[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> s[i];

    int L = 0, R = N, i = 1;
    while (L ^ R) {
        bool flag = true;
        for (int l = L, r = R - 1; l ^ r; ++l, --r)
            if (s[l] ^ s[r]) {
                flag = s[l] < s[r];
                break;
            }
        cout << (flag ? s[L++] : s[--R]);
        if (i++ % 80 == 0) cout << '\n';
    }
    return 0;
}
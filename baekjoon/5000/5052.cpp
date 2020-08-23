#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1e4;
const string ans[2] = {"YES\n", "NO\n"};

string a[mxN];

int solve() {
    int N; cin >> N;
    loop(i, N) cin >> a[i];

    sort(a, a + N);

    loop(i, N - 1) if (a[i].size() < a[i + 1].size()) {
        bool flag = true;
        loop(j, a[i].size()) {
            if (a[i][j] ^ a[i + 1][j]) {
                flag = false;
                break;
            }
        }
        if (flag) return 1;
    }
    return 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) cout << ans[solve()];
    return 0;
}
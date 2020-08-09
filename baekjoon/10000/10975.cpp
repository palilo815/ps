#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 50;

int a[mx], b[mx];
bool in[mx + 2];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i];

    copy(a, a + N, b);
    sort(b, b + N);

    int ans = 0;
    loop(i, N) {
        int j = lower_bound(b, b + N, a[i]) - b + 1;
        if (!in[j - 1] && !in[j + 1]) ++ans;
        in[j] = true;
    }
    cout << ans;
    return 0;
}
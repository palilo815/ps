#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 20000;

int A[max_N], B[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int a, b, ans = 0;
        cin >> a >> b;
        loop(i, a) cin >> A[i];
        loop(i, b) cin >> B[i];
        sort(A, A + a);
        loop(i, b)
            ans += (A + a) - upper_bound(A, A + a, B[i]);
        cout << ans << '\n';
    }
    return 0;
}
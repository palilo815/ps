#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int sakura[10];
int mul(int s, int e)
{
    int ret = 1;
    while (s < e) ret *= sakura[s++];
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, ans = 0;
    cin >> n;
    loop(i, n) cin >> sakura[i];
    for (int a = 1; a < n - 2; ++a) {
        int tmp_a = mul(0, a);
        for (int b = a + 1; b < n - 1; ++b) {
            int tmp_b = mul(a, b);
            for (int c = b + 1; c < n; ++c) {
                int tmp_c = mul(b, c), tmp_d = mul(c, n);
                ans = max(ans, tmp_a + tmp_b + tmp_c + tmp_d);
            }
        }
    }
    cout << ans;
    return 0;
}
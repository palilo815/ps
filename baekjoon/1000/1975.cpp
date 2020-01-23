#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int ans = 0;
        int n; cin >> n;
        for (int i = 2;i <= n;++i) {
            // i진법의 끝자리 0을 더해준다.
            int tmp = n;
            while (tmp % i == 0) {
                tmp /= i;
                ++ans;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
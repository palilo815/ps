#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int ans = 0, MIN = INT32_MAX;
        loop(i, 7) {
            int n; cin >> n;
            if (n % 2 == 0) {
                ans += n;
                if (n < MIN) MIN = n;
            }
        }
        cout << ans << ' ' << MIN << '\n';
    }
    return 0;
}
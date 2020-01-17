#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int dog[2][2], psn[3];
    loop(i, 2) loop(j, 2) cin >> dog[i][j];
    loop(i, 3) cin >> psn[i];
    loop(i, 3) {
        int ans = 0;
        loop(d, 2) {
            int T = psn[i] % (dog[d][0] + dog[d][1]);
            if (T > 0 && T <= dog[d][0]) ++ans;
        }
        cout << ans << '\n';
    }
    return 0;
}
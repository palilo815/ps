#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        vector<int> vt(4);
        loop(i, 4) { char c; cin >> c; vt[i] = c - '0'; }
        int ans = 0;
        while (1) {
            if (vt[0] == 6 && vt[1] == 1 && vt[2] == 7 && vt[3] == 4) {
                cout << ans << '\n';
                break;
            }
            vector<int> tmp = vt;
            sort(vt.begin(), vt.end(), greater<int>());
            sort(tmp.begin(), tmp.end());
            for (int i = 3; i >= 0; --i) {
                vt[i] -= tmp[i];
                if (vt[i] < 0) vt[i] += 10, --vt[i - 1];
            }
            ++ans;
        }
    }
    return 0;
}
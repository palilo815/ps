#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int a, b; cin >> a >> b;

        int dist = b - a;
        int mov = 1;
        int ans = 0;

        while (dist >= 2 * mov) {
            dist -= 2 * mov++;
            ans += 2;
        }
        
        if (dist) ++ans;
        if (dist > mov) ++ans;
        cout << ans << '\n';
    }
    return 0;
}
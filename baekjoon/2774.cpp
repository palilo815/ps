#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool check[10];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        memset(check, 0, sizeof(check));
        int n; cin >> n;
        while (n) {
            check[n % 10] = true;
            n /= 10;
        }
        int ans = 0;
        loop(i, 10)
            if (check[i]) ++ans;
        cout << ans << '\n';
    }
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool sit[101];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, ans = 0;
    cin >> n;
    while (n-- > 0) {
        int x; cin >> x;
        if (sit[x]) ans++;
        else sit[x] = true;
    }
    cout << ans;
    return 0;
}
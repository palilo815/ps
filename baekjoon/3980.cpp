#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[11][11], ans;
void max_stat(int num, int select, int stat)
{
    if (num == 11) {
        ans = max(ans, stat);
        return;
    }
    loop(i, 11)
        if (arr[num][i] && !(select & (1 << i)))
            max_stat(num + 1, select | (1 << i), stat + arr[num][i]);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    int T; cin >> T;
    while (T--) {
        ans = 0;
        loop(i, 11) loop(j, 11)
            cin >> arr[i][j];
        max_stat(0, 0, 0);
        cout << ans << '\n';
    }
    return 0;
}
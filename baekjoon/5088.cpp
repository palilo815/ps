#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int Map[100][100], row, col;
    while (cin >> row >> col) {
        if (!row && !col) break;
        memset(Map, 0, sizeof(Map));
        int n, ans = 0;

        cin >> n;
        while (n--) {
            int r, c; cin >> r >> c;
            ++Map[r][c];
        }

        cin >> n;
        while (n--) {
            int r, c; cin >> r >> c;
            ans += Map[r][c];
        }
        cout << ans << '\n';
    }
    return 0;
}
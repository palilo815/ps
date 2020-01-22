#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int DP[41][41];
int LOG[41][41];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string a, b; cin >> a >> b;
    int len_a = a.size(), len_b = b.size();
    loop(i, len_a) loop(j, len_b) {
        if (a[i] == b[j]) {
            DP[i + 1][j + 1] = DP[i][j] + 1;
            LOG[i + 1][j + 1] = 3;
        }
        else {
            if (DP[i][j + 1] > DP[i + 1][j]) {
                DP[i + 1][j + 1] = DP[i][j + 1];
                LOG[i + 1][j + 1] = 2;
            }
            else {
                DP[i + 1][j + 1] = DP[i + 1][j];
                LOG[i + 1][j + 1] = 1;
            }
        }
    }

    int i = len_a, j = len_b;
    string ans = "";
    while (i > 0 && j > 0) {
        if (LOG[i][j] == 3) {
            --i, --j;
            ans += a[i];
        }
        else if (LOG[i][j] == 2) --i;
        else --j;
    }
    for (i = ans.size() - 1;i >= 0;--i)
        cout << ans[i];
    return 0;
}
#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int DP[10001], coin[20];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t, n, m;
    cin >> t;
    while (t--) {
        memset(DP, 0, sizeof(DP));
        DP[0] = 1;
        cin >> n;
        loop(i, n) cin >> coin[i];
        cin >> m;
        loop(i, n) {
            int cost = coin[i];
            for (int j = cost;j <= m;++j)
                DP[j] += DP[j - cost];
        }
        cout << DP[m] << '\n';
    }
    return 0;
}
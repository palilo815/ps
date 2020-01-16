#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

// 노맛인지 아닌지 체크
bool NoMat[201][201];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m; cin >> n >> m;
    while (m--) {
        int a, b; cin >> a >> b;
        NoMat[a][b] = NoMat[b][a] = true;
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1;j <= n; ++j) {
            if (NoMat[j][i]) continue;
            for (int k = j + 1; k <= n; ++k) {
                if (NoMat[k][i] || NoMat[k][j]) continue;
                ++ans;
            }
        }
    }
    cout << ans;
    return 0;
}
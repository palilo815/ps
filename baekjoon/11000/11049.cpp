#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int DP[500][500], RC[501];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> RC[i] >> RC[i + 1];
    /*
        DP[a][b] : a부터 b까지 matrix를 곱하는데 드는 최소비용
        따라서 정답은 DP[0][n-1]를 출력하면 되고
        a > b인 부분은 사용하지 않는다.
    */
    for (int gap = 1; gap < n; ++gap) {
        for (int i = 0; i + gap < n; ++i) {
            int tmp = INT_MAX;
            for (int j = i; j < i + gap; ++j)
                tmp = min(tmp, DP[i][j] + DP[j + 1][i + gap] + RC[i] * RC[j + 1] * RC[i + gap + 1]);
            DP[i][i + gap] = tmp;
        }
    }
    cout << DP[0][n - 1];
    return 0;
}
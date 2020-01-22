#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[100000], DP[2][100000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    int max_num = INT_MIN;
    loop(i, N) {
        cin >> arr[i];
        max_num = max(max_num, arr[i]);
    }
    DP[0][0] = arr[0], DP[1][0] = 0;
    for (int i = 1; i < N; ++i) {
        DP[0][i] = max(DP[0][i - 1] + arr[i], arr[i]);
        DP[1][i] = max(DP[1][i - 1] + arr[i], DP[0][i - 1]);
    }
    int ans = INT32_MIN;
    loop(i, 2) loop(j, N)
        ans = max(ans, DP[i][j]);
    if (ans == 0) ans = max_num;
    cout << ans;
    return 0;
}
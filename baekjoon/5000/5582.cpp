#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_len = 4000;

int DP[max_len + 1][max_len + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string a, b; cin >> a >> b;
    int A = a.size(), B = b.size(), ans = 0;
    // 연속된 문자열을 고르는 문제므로
    // a[i-1] != b[j-1]일 경우 DP를 0으로 만들고,
    // 최댓값이 DP[A][B]에 저장되지 않으므로
    // ans를 따로 구해준다.
    // 그 이외에는 LCS문제랑 같다.
    for (int i = 1;i <= A;++i)
        for (int j = 1;j <= B;++j) {
            if (a[i - 1] == b[j - 1]) {
                DP[i][j] = DP[i - 1][j - 1] + 1;
                ans = max(ans, DP[i][j]);
            }
            else DP[i][j] = 0;
        }
    cout << ans;
    return 0;
}
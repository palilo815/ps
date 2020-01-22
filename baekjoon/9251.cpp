#include <bits/stdc++.h>
using namespace std;

int DP[1001][1001];
int main()
{
    string a, b;
    cin >> a >> b;
    int len_a = a.size(), len_b = b.size();
    for (int i = 1;i <= len_a;++i)
        for (int j = 1;j <= len_b;++j) {
            if (a[i - 1] == b[j - 1])
                DP[i][j] = DP[i - 1][j - 1] + 1;
            else
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
        }
    cout << DP[len_a][len_b];
    return 0;
}
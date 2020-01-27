#include <bits/stdc++.h>
using namespace std;

int DP[1001][1001], cache[1001][1001];
int main()
{
    string a, b;
    cin >> a >> b;
    int len_a = a.size(), len_b = b.size();
    for (int i = 1;i <= len_a;++i)
        for (int j = 1;j <= len_b;++j) {
            if (a[i - 1] == b[j - 1]) {
                DP[i][j] = DP[i - 1][j - 1] + 1;
                cache[i][j] = 3;
            }
            else {
                if (DP[i - 1][j] > DP[i][j - 1]) {
                    DP[i][j] = DP[i - 1][j];
                    cache[i][j] = 1;
                }
                else {
                    DP[i][j] = DP[i][j - 1];
                    cache[i][j] = 2;
                }
            }
        }
    cout << DP[len_a][len_b] << '\n';
    stack<char> stk;
    while (cache[len_a][len_b])
        switch (cache[len_a][len_b]) {
        case 3:
            --len_a, --len_b;
            stk.push(a[len_a]);
            break;
        case 2:
            --len_b;
            break;
        case 1:
            --len_a;
        }
    while (!stk.empty()) {
        cout << stk.top();
        stk.pop();
    }
    return 0;
}
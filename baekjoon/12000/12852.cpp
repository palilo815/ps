#include <iostream>
using namespace std;
const int max_N = 1000000;

int DP[max_N + 1], parent[max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // basis : DP[1] = 0, parent[1] = 0

    int n; cin >> n;
    for (int i = 2; i <= n; ++i) {
        int cnt = DP[i - 1], p = i - 1;
        if (i % 2 == 0 && DP[i / 2] < cnt)
            cnt = DP[i / 2], p = i / 2;
        if (i % 3 == 0 && DP[i / 3] < cnt)
            cnt = DP[i / 3], p = i / 3;
        DP[i] = cnt + 1;
        parent[i] = p;
    }
    cout << DP[n] << '\n';
    for (int i = n; i != 0; i = parent[i])
        cout << i << ' ';
    return 0;
}
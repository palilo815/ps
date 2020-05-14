#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 2500;

int DP[max_N + 1];
bool pallin[max_N][max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    string s; cin >> s;
    int N = s.size();

    loop(i, N) {
        pallin[i][i] = true;
        int l = i - 1, r = i + 1;
        while (0 <= l && r < N && s[l] == s[r])
            pallin[l--][r++] = true;
    }
    loop(i, N - 1) {
        int l = i, r = i + 1;
        while (0 <= l && r < N && s[l] == s[r])
            pallin[l--][r++] = true;
    }

    memset(DP + 1, 0x3f, sizeof(int) * N);
    loop(i, N) for (int j = i; j < N; ++j)
        if (pallin[i][j])
            DP[j + 1] = min(DP[j + 1], DP[i] + 1);
    cout << DP[N];
    return 0;
}
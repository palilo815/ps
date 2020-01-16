#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

// DP[key_pos][bridge][len]
int DP[20][2][100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string key, brid[2];
    cin >> key >> brid[0] >> brid[1];
    int len = brid[0].size(), key_len = key.size();

    // basis : key의 첫 글자에서 시작.
    loop(i, len) loop(j, 2)
        if (brid[j][i] == key[0]) DP[0][j][i] = 1;
    
    loop(k, key_len - 1) loop(b, 2)loop(l, len) {
        if (DP[k][b][l]) {
            char to = key[k + 1];
            for (int i = l + 1; i < len; ++i)
                if (brid[1 - b][i] == to)
                    DP[k + 1][1 - b][i] += DP[k][b][l];
        }
    }

    int ans = 0;
    loop(b, 2) loop(l, len)
        ans += DP[key_len - 1][b][l];
    cout << ans;
    return 0;
}
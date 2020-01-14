#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int row, col, k, key_len, mov_y[4] = { -1,1,0,0 }, mov_x[4] = { 0,0,-1,1 };
char Board[100][100];
int Cache[100][100][80];
string key;

int DP(int r, int c, int start)
{
    if (start == key_len - 1) return 1;
    int& ret = Cache[r][c][start];
    if (ret != -1) return ret;

    ret = 0;
    loop(i, 4) {
        for (int j = 1; j <= k; ++j) {
            int R = mov_y[i] * j + r, C = mov_x[i] * j + c;
            if (R < 0 || R >= row || C < 0 || C >= col) continue;
            if (Board[R][C] == key[start + 1])
                ret += DP(R, C, start + 1);
        }
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(Cache, -1, sizeof(Cache));
    cin >> row >> col >> k;
    loop(i, row) loop(j, col) cin >> Board[i][j];
    cin >> key;
    key_len = key.length();
    int Ans = 0;

    loop(i, row) loop(j, col) {
        if (Board[i][j] == key[0])
            Ans += DP(i, j, 0);
    }
    cout << Ans;
    return 0;
}
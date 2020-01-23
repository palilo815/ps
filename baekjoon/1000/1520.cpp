#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int mat[500][500], cache[500][500];
int n, m, mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int TopDown(int r, int c)
{
    int& ret = cache[r][c];
    if (ret != -1) return ret;
    ret = 0;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= n || C < 0 || C >= m) continue;
        if (mat[R][C] > mat[r][c])
            ret += TopDown(R, C);
    }
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(cache, -1, sizeof(cache));
    cin >> n >> m;
    loop(i, n) loop(j, m) cin >> mat[i][j];
    cache[0][0] = 1;
    cout << TopDown(n - 1, m - 1);
    return 0;
}
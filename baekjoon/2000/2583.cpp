#include <bits/stdc++.h>
#define loop(i,n) for(int i=0; i<n; ++i)
using namespace std;

int row, col;
int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
bool colour[100][100];

int DFS(int r, int c)
{
    colour[r][c] = true;
    int ret = 1;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || colour[R][C]) continue;
        ret += DFS(R, C);
    }
    return ret;
}

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> row >> col >> N;
    while (N--) {
        int r1, c1, r2, c2; cin >> c1 >> r1 >> c2 >> r2;
        for (int i = r1; i < r2; ++i)
            for (int j = c1; j < c2; ++j)
                colour[i][j] = true;
    }

    vector<int> ans;
    loop(i, row) loop(j, col)
        if (!colour[i][j])
            ans.push_back(DFS(i, j));
    sort(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for(int x : ans)
        cout << x << ' ';
    return 0;
}
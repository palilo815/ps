#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
const int max_N = 25;

int N;
char mat[max_N][max_N];
bool visited[max_N][max_N];

int DFS(int r, int c) {
    int ret = 1;
    visited[r][c] = true;

    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= N || C < 0 || C >= N || mat[R][C] == '0' || visited[R][C]) continue;
        ret += DFS(R, C);
    }
    return ret;
}

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<int> ans;
    cin >> N;
    loop(i, N) loop(j, N) cin >> mat[i][j];
    loop(i, N) loop(j, N) if (mat[i][j] == '1' && !visited[i][j])
        ans.emplace_back(DFS(i, j));

    sort(ans.begin(), ans.end());
    cout << ans.size();
    for (int x : ans) cout << '\n' << x;
    return 0;
}
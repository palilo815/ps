#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

char map[25][25];
bool visited[25][25]{};
int mov_i[4] = { 0,0,-1,1 };
int mov_j[4] = { 1,-1,0,0 };
int n;

int dfs(int a, int b)
{
    int count = 1;
    visited[a][b] = true;
    for (int i = 0; i < 4; i++) {
        int y = a + mov_i[i];
        if (y == -1 || y == n) continue;
        int x = b + mov_j[i];
        if (x == -1 || x == n) continue;
        if (map[y][x] == '1' && !visited[y][x])
            count += dfs(y, x);
    }
    return count;
}

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    vector<int> ans;
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> map[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (map[i][j] == '1' && !visited[i][j])
                ans.push_back(dfs(i, j));

    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << '\n';
    return 0;
}
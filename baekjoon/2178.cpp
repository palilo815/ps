#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

int mov_i[4] = { 0,1,0,-1 };
int mov_j[4] = { 1,0,-1,0 };

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int row, col;
    cin >> row >> col;
    char** mat = new char* [row];
    for (int i = 0;i < row;i++)
        mat[i] = new char[col];
    for (int i = 0;i < row;i++)
        for (int j = 0;j < col;j++)
            cin >> mat[i][j];

    queue<pair<int, int>> q;
    q.push(make_pair(0, 0));
    q.push(make_pair(-1, -1));
    mat[0][0] = '0';
    int ans = 1;
    while (!q.empty()) {
        int i = q.front().first, j = q.front().second;
        if (i == row - 1 && j == col - 1) break;
        if (i == -1) {
            q.pop();
            ans++;
            q.push(make_pair(-1, -1));
            continue;
        }
        q.pop();
        for (int a = 0;a < 4;a++) {
            int next_i = i + mov_i[a], next_j = j + mov_j[a];
            if (next_i == -1 || next_i == row) continue;
            if (next_j == -1 || next_j == col) continue;
            if (mat[next_i][next_j] == '1') {
                mat[next_i][next_j] = '0';
                q.push(make_pair(next_i, next_j));
            }
        }
    }
    cout << ans;
    return 0;
}
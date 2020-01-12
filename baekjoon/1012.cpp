#include <iostream>
using namespace std;

int **map;
bool **visited;
int mov_i[4] = {0, 0, -1, 1};
int mov_j[4] = {1, -1, 0, 0};
int row, col;
void Init() {
    map = new int *[row];
    visited = new bool *[row];
    for (int i = 0; i < row; i++) {
        map[i] = new int[col]{};
        visited[i] = new bool[col]{};
    }
}
void Dele() {
    for (int i = 0; i < row; i++) {
        delete (map[i]);
        delete (visited[i]);
    }
    delete (map);
    delete (visited);
}
void dfs(int a, int b) {
    visited[a][b] = true;
    for (int i = 0; i < 4; i++) {
        int y = a + mov_i[i];
        if (y == -1 || y >= row) continue;
        int x = b + mov_j[i];
        if (x == -1 || x >= col) continue;
        if (map[y][x] == 1 && !visited[y][x])
            dfs(y, x);
    }
}

int main() {
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int t, k;
    cin >> t;
    while (t-- > 0) {
        int count = 0;
        cin >> col >> row >> k;
        Init();
        while (k-- > 0) {
            int j, i;
            cin >> j >> i;
            map[i][j] = 1;
        }

        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                if (map[i][j] == 1 && !visited[i][j]) {
                    dfs(i, j);
                    count++;
                }
        cout << count << '\n';
        Dele();
    }
    return 0;
}
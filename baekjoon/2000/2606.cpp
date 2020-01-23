#include<iostream>
#include<algorithm>
using namespace std;

int** mat;
int v;
int ans = -1;
bool* visited;
void DFS(int start)
{
    ans++;
    visited[start] = true;
    for (int i = 1; i < v; i++)
        if (mat[start][i] == 1 && !visited[i])
            DFS(i);
}

int main()
{
    int e, x, y;
    cin >> v >> e;
    v++;
    mat = new int* [v];
    for (int i = 1;i < v;i++)
        mat[i] = new int[v] {};
    visited = new bool[v] {};
    while (e-- > 0) {
        cin >> x >> y;
        mat[x][y] = 1, mat[y][x] = 1;
    }
    DFS(1);
    cout << ans;
    return 0;
}
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

int** mat;
int mat_size;
bool* visited;
void DFS(int start)
{
    visited[start] = true;
    cout << start << ' ';
    for (int i = 1; i < mat_size; i++)
        if (mat[start][i] == 1 && !visited[i])
            DFS(i);
}
void BFS(int start)
{
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        cout << here << ' ';
        for (int i = 1; i < mat_size; i++)
            if (mat[here][i] == 1 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
    }
}

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int m, v, x, y;
    cin >> mat_size >> m >> v;
    mat_size++;
    mat = new int* [mat_size];
    for (int i = 0; i < mat_size;i++)
        mat[i] = new int [mat_size] {};

    while (m-- > 0) {
        cin >> x >> y;
        mat[x][y] = 1, mat[y][x] = 1;
    }
    visited = new bool[mat_size] {};
    DFS(v);
    cout << '\n';
    delete(visited);
    visited = new bool[mat_size] {};
    BFS(v);
    return 0;
}
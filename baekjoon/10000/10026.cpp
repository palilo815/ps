#include <bits/stdc++.h>
#define loop(i,n) for(int i=0; i<n; ++i)
#define P pair<int,int>
using namespace std;

int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
char colour[100][100];
bool visited[100][100];
void DFS(int r, int c, int N)
{
    visited[r][c] = true;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= N || C < 0 || C >= N || visited[R][C]) continue;
        if(colour[R][C] == colour[r][c])
            DFS(R, C, N);
    }
}
int count(int N)
{
    int ret = 0;
    loop(i, N) loop(j, N)
        if (!visited[i][j]) {
            DFS(i, j, N);
            ++ret;
        }
    return ret;
}
int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> colour[i][j];
    cout << count(N) << ' ';

    memset(visited, 0, sizeof(visited));
    loop(i, N) loop(j, N)
        if (colour[i][j] == 'G')
            colour[i][j] = 'R';
    cout << count(N);
    return 0;
}
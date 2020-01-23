#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

int mov[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int mov_Knight[8][2] = { {-1,-2},{-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2} };
bool visited[31][200][200];	// chance + (y,x)
char Map[200][200];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, k;
    cin >> k >> col >> row;
    loop(i, row) loop(j, col) cin >> Map[i][j];
    queue<P> q;
    q.push({ 0,k }), q.push({ -1, -1 });
    visited[k][0][0] = true;
    int ans = 0;
    while (1) {
        int r = q.front().first / 200, c = q.front().first % 200, chance = q.front().second; q.pop();

        // pivot
        if (chance == -1) {
            if (q.empty()) break;
            ans++; q.push(make_pair(-1, -1));
            continue;
        }

        // 도착
        if (r == row - 1 && c == col - 1) break;

        // 원숭이
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col) continue;
            if (Map[R][C] == '0' && !visited[chance][R][C]) {
                visited[chance][R][C] = true;
                q.push(make_pair(200 * R + C, chance));
            }
        }

        // 찬스가 남아있으면 말처럼 이동
        if (chance)
            loop(i, 8) {
            int R = r + mov_Knight[i][0], C = c + mov_Knight[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col) continue;
            if (Map[R][C] == '0' && !visited[chance - 1][R][C]) {
                visited[chance - 1][R][C] = true;
                q.push(make_pair(200 * R + C, chance - 1));
            }
        }
    }

    if (q.empty()) cout << -1;
    else cout << ans;
    return 0;
}
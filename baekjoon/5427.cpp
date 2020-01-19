#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

char Building[1000][1000];
int row, col, mov[4][2] = { -1,0,0,-1,0,1,1,0 };

void BFS(queue<P>& q, bool man, int& escape)
{
    while (1) {
        int y = q.front().first, x = q.front().second; q.pop();
        // pivot
        // 만약 사람이 더이상 움직일 수 없다면 실패다. (escape = 1)
        if (y == -1) {
            if (man && q.empty()) escape = 1;
            q.push({ -1,-1 });
            return;
        }
        // find answer
        // 사람이 빌딩의 외곽에 도착하면 성공이다. (escape = 2)
        if (man && (y == 0 || y == row - 1 || x == 0 || x == col - 1)) {
            escape = 2;
            return;
        }
        // move
        loop(i, 4) {
            int Y = y + mov[i][0], X = x + mov[i][1];
            if (Y < 0 || Y >= row || X < 0 || X >= col) continue;
            // 사람일 경우, '.'으로만 다닐 수 있다.
            if (man) {
                if (Building[Y][X] == '.') {
                    Building[Y][X] = '@';
                    q.push({ Y,X });
                }
            }
            // 불은 '#'이 아닌 모든 곳으로 다닐 수 있다.
            else {
                if (Building[Y][X] != '#') {
                    Building[Y][X] = '#';
                    q.push({ Y,X });
                }
            }
        }
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        // ** initialize **
        queue<P> man, fire;
        cin >> col >> row;
        loop(i, row) loop(j, col) {
            char c; cin >> c;
            if (c == '@') man.push(make_pair(i, j));
            else if (c == '*') c = '#', fire.push(make_pair(i, j));
            Building[i][j] = c;
        }
        man.push({ -1,-1 }), fire.push({ -1,-1 });

        // escape == 0 : 탐색중, 1 : 불가능, 2 : 성공
        int escape = 0, ans = 0;
        while(!escape){
            BFS(fire, false, escape);
            BFS(man, true, escape);
            ++ans;
        }

        if (escape == 1) cout << "IMPOSSIBLE\n";
        else cout << ans << '\n';
    }
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

int mov[4][2] = { 1,0,0,-1,-1,0,0,1 };	// 남 서 북 동
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    set<P> cache;
    cache.insert(make_pair(0, 0));
    int y = 0, x = 0, d = 0, N;
    int y_min = 0, x_min = 0, y_max = 0, x_max = 0;
    cin >> N;

    // 처음 시작 좌표를 (0,0)이라 했을 때,
    // 방문하는 좌표를 전부 cache에 집어넣는다.
    while (N--) {
        char op; cin >> op;
        if (op == 'R') d = (d + 1) % 4;
        else if (op == 'L') d = (d + 3) % 4;
        else {
            y = y + mov[d][0], x = x + mov[d][1];
            y_min = min(y_min, y), y_max = max(y_max, y);
            x_min = min(x_min, x), x_max = max(x_max, x);
            cache.insert(make_pair(y, x));
        }
    }

    // 방문한 최대/최소 범위에 맞게 maze를 만들고 전부 #으로 채운다.
    int row = y_max - y_min + 1, col = x_max - x_min + 1;
    char** maze = new char* [row];
    loop(i, row) maze[i] = new char[col];
    loop(i, row) loop(j, col) maze[i][j] = '#';

    // cache에 적어놓은 좌표에 해당하는 maze는 .로 바꾼다.
    for (P p : cache)
        maze[p.first - y_min][p.second - x_min] = '.';
    loop(i, row) {
        loop(j, col) cout << maze[i][j];
        cout << '\n';
    }
    return 0;
}
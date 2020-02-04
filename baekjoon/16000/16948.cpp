#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;
const int max_N = 200;

int mov[6][2] = { -2,-1,-2,1,0,-2,0,2,2,-1,2,1 };
bool visited[max_N][max_N];
int main()
{
    int N, y1, x1, y2, x2;
    cin >> N >> y1 >> x1 >> y2 >> x2;

    queue<P> q;
    q.push({ y1, x1 }), q.push({ -1, -1 });
    visited[y1][x1] = true;
    int ans = 0;
    while (1) {
        int y = q.front().first, x = q.front().second; q.pop();
        if (y == -1) {
            if (q.empty()) {
                ans = -1;
                break;
            }
            ++ans;
            q.push({ -1,-1 });
            continue;
        }
        if (y == y2 && x == x2) break;
        loop(i, 6) {
            int Y = y + mov[i][0], X = x + mov[i][1];
            if (Y < 0 || Y >= N || X < 0 || X >= N || visited[Y][X]) continue;
            visited[Y][X] = true;
            q.push({ Y,X });
        }
    }
    cout << ans;
    return 0;
}
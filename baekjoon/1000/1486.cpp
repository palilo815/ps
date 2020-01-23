#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

int Map[25][25], Up[25][25], Down[25][25];
int mov_y[4] = { -1,1,0,0 }, mov_x[4] = { 0,0,-1,1 };

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, T, D;
    cin >> row >> col >> T >> D;
    loop(i, row) loop(j, col) {
        Up[i][j] = INT32_MAX / 2;
        Down[i][j] = INT32_MAX / 2;
    }
    loop(i, row) loop(j, col) {
        char c; cin >> c;
        if (c < 'a') Map[i][j] = c - 'A';
        else Map[i][j] = c - 'a' + 26;
    }

    Up[0][0] = Down[0][0] = 0;
    priority_queue<P, vector<P>, greater<P>> pq;

    // Up[i][j] : 출발지에서 (i,j)로 올라가는데 드는 시간
    // Down[i][j] : (i,j)에서 출발지로 내려가는데 드는 시간
    // 을 두 번의 BFS로 구한다.
    // 만약 Up+Down이 제한 시간을 초과하면 불가능한 경우니 패스하고
    // 제한시간내에 도착하는 곳 중 가장 높은 곳을 출력하면 된다.

    pq.push(make_pair(0, 0));
    while (!pq.empty()) {
        int cost = pq.top().first, r = pq.top().second / 25, c = pq.top().second % 25;
        pq.pop();
        if (Up[r][c] < cost) continue;
        loop(i, 4) {
            int R = r + mov_y[i], C = c + mov_x[i];
            if (R < 0 || R >= row || C < 0 || C >= col) continue;
            int Gap = abs(Map[R][C] - Map[r][c]);
            if (Gap > T) continue;
            int NextCost = cost;;
            if (Map[R][C] <= Map[r][c]) NextCost += 1;
            else NextCost += Gap * Gap;
            if (Up[R][C] > NextCost) {
                Up[R][C] = NextCost;
                pq.push(make_pair(NextCost, 25 * R + C));
            }
        }
    }
    pq.push(make_pair(0, 0));
    while (!pq.empty()) {
        int cost = pq.top().first, r = pq.top().second / 25, c = pq.top().second % 25;
        pq.pop();
        if (Down[r][c] < cost) continue;
        loop(i, 4) {
            int R = r + mov_y[i], C = c + mov_x[i];
            if (R < 0 || R >= row || C < 0 || C >= col) continue;
            int Gap = abs(Map[R][C] - Map[r][c]);
            if (Gap > T) continue;
            int NextCost = cost;;
            if (Map[R][C] < Map[r][c]) NextCost += Gap * Gap;
            else NextCost += 1;
            if (Down[R][C] > NextCost) {
                Down[R][C] = NextCost;
                pq.push(make_pair(NextCost, 25 * R + C));
            }
        }
    }
    int ans = 0;
    loop(i, row) loop(j, col)
        if (Up[i][j] + Down[i][j] <= D)
            ans = max(ans, Map[i][j]);
    cout << ans;
    return 0;
}
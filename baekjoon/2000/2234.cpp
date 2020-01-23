#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int row, col, castle[50][50], room[50][50];
int mov[4][2] = { 0,-1,-1,0,0,1,1,0 };

// room[r][c]와 인접한 모든 곳을 num으로 채우고
// 그 넓이를 return한다.
int DFS(int r, int c, int num)
{
    int ret = 1;
    room[r][c] = num;
    loop(i, 4) {
        if ((1 << i) & castle[r][c]) continue;
        int R = r + mov[i][0], C = c + mov[i][1];
        if (!room[R][C])
            ret += DFS(R, C, num);
    }
    return ret;
}
void make_couple(int r, int c, int& ans, vector<int>& vt)
{
    int u = room[r][c];
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col) continue;
        int v = room[R][C];
        if (v > u) ans = max(ans, vt[u] + vt[v]);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<int> room_size(1);
    int room_num = 0, max_room = 0, couple_room = 0;
    cin >> col >> row;
    loop(i, row) loop(j, col)
        cin >> castle[i][j];

    // 방마다 번호를 1부터 차례로 부여한다.
    // room[i][j] = n이라면
    // castle[i][j]는 n번방이란 뜻

    loop(i, row) loop(j, col)
        // 만약 room[i][j] == 0이라면
        // (아직 이 방을 세지 않았다면)
        if (!room[i][j]) {
            int S = DFS(i, j, ++room_num);
            max_room = max(max_room, S);
            room_size.push_back(S);
        }
    // 이제 room_size[i]에는 i번 방의 크기가 들어있다.

    // 상하좌우에 다른 room_num을 가진 방이 있으면
    // 서로 room_size를 더해본다.
    loop(i, row) loop(j, col)
        make_couple(i, j, couple_room, room_size);

    cout << room_num << '\n' << max_room << '\n' << couple_room;
    return 0;
}
#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

// M에는 해당 칸에 있는 로봇의 번호를
// robot에는 해당 로봇의 위치와 방향을 저장.
int M[101][101], mov[4][2] = { 1,0,0,1,-1,0,0,-1 }; // N E S W
int robot[101][3];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // ** initialize **
    int row, col, N_robot, N_inst;
    cin >> col >> row >> N_robot >> N_inst;
    for (int i = 1;i <= N_robot;++i) {
        int r, c, d; char D; cin >> c >> r >> D;
        M[r][c] = i;
        robot[i][0] = r, robot[i][1] = c;
        if (D == 'N') d = 0;
        else if (D == 'E') d = 1;
        else if (D == 'S') d = 2;
        else d = 3;
        robot[i][2] = d;
    }

    // ** simulation **
    bool crash = false;
    while (N_inst--) {
        int idx, t; char inst;
        cin >> idx >> inst >> t;

        // idx번 로봇의 정보를 읽어온다.
        int r = robot[idx][0], c = robot[idx][1], d = robot[idx][2];
        // 로봇을 새로 옮기기 때문에, 이전 위치의 M을 0으로 만듦
        M[r][c] = 0;

        // 좌회전 == 우회전 * 3
        if (inst == 'L')
            d = (d + 3 * t) % 4;
        // 우회전
        else if (inst == 'R')
            d = (d + t) % 4;
        // 이동
        else
            while (t--) {
                r += mov[d][0], c += mov[d][1];
                if (r < 1 || r > row || c < 1 || c > col) {
                    cout << "Robot " << idx << " crashes into the wall";
                    crash = true; break;
                }
                else if (M[r][c]) {
                    cout << "Robot " << idx << " crashes into robot " << M[r][c];
                    crash = true; break;
                }
            }
        
        // crash라면 종료, 아니라면 이동 후 정보를 M과 robot에 저장
        if (crash) break;
        robot[idx][0] = r, robot[idx][1] = c, robot[idx][2] = d;
        M[r][c] = idx;
    }
    if (!crash) cout << "OK";
    return 0;
}
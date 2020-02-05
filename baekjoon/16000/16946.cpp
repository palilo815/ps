#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000;

int row, col, mov[4][2] = { -1,0,0,-1,0,1,1,0 };
int mat[max_N][max_N];

int flood_fill(int r, int c, int colour)
{
    int ret = 1;
    mat[r][c] = colour;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || mat[R][C]) continue;
        ret += flood_fill(R, C, colour);
    }
    return ret;
}

// r,c를 부수고 얻을 수 있는 최대 영역
int crash(vector<int>& cnt, int r, int c)
{
    // 부신 벽 자신을 무조건 포함하므로 1
    int ret = 1;
    // 인접한 영역의 색깔 저장하는 vt
    vector<int> vt;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || mat[R][C] == -1) continue;

        // 같은 영역을 중복해서 세지 않아야 한다.
        // 내가 고른 색깔을 저장해놓은 vt에 colour가 있는지 확인.
        // 있다면 colour = 0으로 만든다. (cnt[0] = 0으로 설정해놨다)
        int colour = mat[R][C];
        for (int x : vt)
            if (x == colour) {
                colour = 0;
                break;
            }
        if (colour) vt.push_back(colour);
        ret += cnt[colour];
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 벽 = -1, 빈 칸 = 0으로 표기한다.
    cin >> row >> col;
    loop(i, row) loop(j, col) {
        char x; cin >> x;
        if (x == '1') mat[i][j] = -1;
    }

    // cnt[0] = 0으로 세팅
    vector<int> cnt(1);
    int colour = 0;

    // 빈 칸을 만나면 해당 영역을 colour로 칠한다.
    // colour는 1부터 차례로 칠해진다.
    // 이 작업이 끝난 후 cnt[i]에는 i색 영역의 넓이가 저장된다.
    loop(i, row) loop(j, col)
        if (!mat[i][j])
            cnt.push_back(flood_fill(i, j, ++colour));

    loop(i, row) {
        loop(j, col)
            if (mat[i][j] == -1)
                cout << crash(cnt, i, j) % 10;
            else cout << 0;
        cout << '\n';
    }
    return 0;
}
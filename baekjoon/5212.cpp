#include <iostream>
#include <algorithm>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int row, col, mov[4][2] = { -1,0,0,-1,0,1,1,0 };
char M_old[10][10], M_new[10][10];

// 주변 바다의 개수 return
int count_sea(int r, int c)
{
    int ret = 0;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || M_old[R][C] == '.') ++ret;
    }
    return ret;
}

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    // ** initialize **
    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> M_old[i][j];

    // 새 지도의 크기를 저장
    int r_min = 10, r_max = 0, c_min = 10, c_max = 0;

    loop(i, row) loop(j, col) {
        // 만약 주변 바다가 3미만이라면, 잠기지 않는다.
        if (M_old[i][j] == 'X' && count_sea(i, j) < 3) {
            M_new[i][j] = 'X';
            r_min = min(i, r_min);
            r_max = max(i, r_max);
            c_min = min(j, c_min);
            c_max = max(j, c_max);
        }
        // 아니면 잠긴다.
        else M_new[i][j] = '.';
    }

    // ** print ans **
    for (int i = r_min;i <= r_max;++i) {
        for (int j = c_min;j <= c_max;++j)
            cout << M_new[i][j];
        cout << '\n';
    }
    return 0;
}
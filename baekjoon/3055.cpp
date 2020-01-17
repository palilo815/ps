#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
char M[50][50];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    queue<P> dochi,  water;
    int row, col, ans_y, ans_x;
    cin >> row >> col;
    loop(i, row) loop(j, col) {
        char c; cin >> c;
        if (c == 'S') dochi.push({ i,j }), c = 'X';
        else if (c == '*') water.push({ i,j }), c = 'X';
        else if (c == 'D') ans_y = i, ans_x = j;
        M[i][j] = c;
    }

    dochi.push({ -1,-1 }), water.push({ -1,-1 });
    // find == 0 : 탐색 진행중
    //      == 1 : 불가능
    //      == 2 : 탈출 성공
    int ans = 0, find = 0;
    while (!find) {
        while (1) { // 물 이동
            int y = water.front().first, x = water.front().second; water.pop();
            if (y == -1) {
                water.push({ y, x });
                break;
            }
            loop(i, 4) {
                int Y = y + mov[i][0], X = x + mov[i][1];
                if (Y < 0 || Y >= row || X < 0 || X >= col || M[Y][X] != '.') continue;
                M[Y][X] = 'X';
                water.push({ Y,X });
            }
        }
        while (1) { // 고슴도치 이동
            int y = dochi.front().first, x = dochi.front().second; dochi.pop();
            if (y == -1) {
                if (dochi.empty()) find = 1;
                else {
                    ++ans;
                    dochi.push({ y, x });
                }
                break;
            }
            if (y == ans_y && x == ans_x) {
                find = 2;
                break;
            }
            loop(i, 4) {
                int Y = y + mov[i][0], X = x + mov[i][1];
                if (Y < 0 || Y >= row || X < 0 || X >= col || M[Y][X] == 'X') continue;
                M[Y][X] = 'X';
                dochi.push({ Y, X });
            }
        }
    }

    if (find == 1) cout << "KAKTUS";
    else cout << ans;
    return 0;
}
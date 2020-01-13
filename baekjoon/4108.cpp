#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char Map[100][100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col;
    while (cin >> row >> col) {
        if (!row && !col) break;
        loop(i, row) loop(j, col) {
            char c; cin >> c;
            if (c == '.') c = '0';
            Map[i][j] = c;
        }
        // 지뢰칸은 *, 아닌 칸은 '0'으로 채웠다.

        // 지뢰와 인접한 칸의 값을 1씩 증가.
        loop(i, row) loop(j, col)
            if (Map[i][j] == '*') {
                loop(y, 3) loop(x, 3) {
                    int Y = i - 1 + y, X = j - 1 + x;
                    if (Y < 0 || Y >= row || X < 0 || X >= col || Map[Y][X] == '*')
                        continue;
                    Map[Y][X]++;
                }
            }


        loop(i, row) {
            loop(j, col) cout << Map[i][j];
            cout << '\n';
        }
    }
    return 0;
}
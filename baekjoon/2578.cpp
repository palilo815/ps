#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int Bingo(int Board[][5], int r, int c)
{
    int ret = 0;
    if (r == c)
        loop(i, 5) {
        if (Board[i][i]) break;
        if (i == 4) ++ret;
    }
    if (r + c == 4)
        loop(i, 5) {
        if (Board[i][4 - i]) break;
        if (i == 4) ++ret;
    }
    loop(i, 5) {
        if (Board[r][i]) break;
        if (i == 4) ++ret;
    }
    loop(i, 5) {
        if (Board[i][c]) break;
        if (i == 4) ++ret;
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int Board[5][5], Num[25];
    loop(i, 5) loop(j, 5)
        cin >> Board[i][j];
    loop(i, 25) cin >> Num[i];

    int Count = 0;
    loop(k, 25) {
        int x = Num[k];
        loop(i, 5) loop(j, 5) {
            if (Board[i][j] == x) {
                Board[i][j] = 0;
                Count += Bingo(Board, i, j);
                if (Count >= 3) { cout << k + 1; return 0; }
                goto OUT;
            }
        }
    OUT:;
    }
    return 0;
}
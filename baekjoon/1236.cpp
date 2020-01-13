#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char castle[50][50];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, R = 0, C = 0;
    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> castle[i][j];

    // guard : 해당 행/열에 경비원이 있는지 여부
    // 만약 없다면 배치해야 한다.
    // R : 배치해야하는 행의 개수
    // C : 배치해야하는 열의 개수
    loop(i, row) {
        bool guard = false;
        loop(j, col)
            if (castle[i][j] == 'X') {
                guard = true;
                break;
            }
        if (!guard) R++;
    }
    loop(j, col) {
        bool guard = false;
        loop(i, row)
            if (castle[i][j] == 'X') {
                guard = true;
                break;
            }
        if (!guard) C++;
    }
    int ans = max(R, C);
    cout << ans;
    return 0;
}
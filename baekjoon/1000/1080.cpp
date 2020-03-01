#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int MAX = 50;

char A[MAX][MAX], B[MAX][MAX];

void rev(int y, int x) {
    loop(i, 3) loop(j, 3) {
        if (A[y + i][x + j] == '0') A[y + i][x + j] = '1';
        else A[y + i][x + j] = '0';
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col;
    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> A[i][j];
    loop(i, row) loop(j, col) cin >> B[i][j];

    // 뒤집기
    int ans = 0;
    loop(i, row - 2) loop(j, col - 2)
        if (A[i][j] != B[i][j]) {
            rev(i, j);
            ++ans;
        }

    // 뒤집은 후에도 같지 않다면 -1
    loop(i, row) loop(j, col)
        if (A[i][j] != B[i][j]) {
            ans = -1;
            break;
        }
    cout << ans;
    return 0;
}
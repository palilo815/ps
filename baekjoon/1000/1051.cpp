#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char arr[50][50];
int main() {
    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> arr[i][j];

    int ans = 0;
    loop(i, row - 1) loop(j, col - 1) for (int k = j + 1; k < col; ++k)
        if (arr[i][j] == arr[i][k]) {
            int dist = k - j;
            if (i + dist >= row || dist <= ans) continue;
            if (arr[i + dist][j] == arr[i][j] && arr[i + dist][k] == arr[i][j])
                ans = dist;
        }

    ++ans;
    cout << ans * ans;
    return 0;
}
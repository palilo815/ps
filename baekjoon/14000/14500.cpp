#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[500][500], row, col;
int nogada(int r, int c)
{
    int ret = 0;
    int base = arr[r][c];
    if (r + 3 < row) ret = max(ret, base + arr[r + 1][c] + arr[r + 2][c] + arr[r + 3][c]);
    if (c + 1 < col) {
        base += arr[r][c + 1];
        if (r + 1 < row) {
            ret = max(ret, base + arr[r + 1][c] + arr[r + 1][c + 1]);
            if (r - 1 >= 0) {
                int tmp = max(max(arr[r - 1][c] + arr[r + 1][c + 1], arr[r + 1][c] + arr[r - 1][c + 1]), max(arr[r - 1][c] + arr[r + 1][c], arr[r - 1][c + 1] + arr[r + 1][c + 1]));
                ret = max(ret, base + tmp);
            }
        }
        if (r + 2 < row) {
            int tmp = max(arr[r + 1][c + 1] + arr[r + 2][c + 1], arr[r + 1][c] + arr[r + 2][c]);
            ret = max(ret, base + tmp);
        }
        if (r - 2 >= 0) {
            int tmp = max(arr[r - 1][c + 1] + arr[r - 2][c + 1], arr[r - 1][c] + arr[r - 2][c]);
            ret = max(ret, base + tmp);
        }
        if (c + 2 < col) {
            if (r - 1 >= 0) ret = max(ret, base + arr[r - 1][c + 1] + arr[r - 1][c + 2]);
            if (r + 1 < row) ret = max(ret, base + arr[r + 1][c + 1] + arr[r + 1][c + 2]);
            base += arr[r][c + 2];
            if (r - 1 >= 0) {
                int tmp = max(arr[r - 1][c], arr[r - 1][c + 1]);
                tmp = max(tmp, arr[r - 1][c + 2]);
                ret = max(ret, base + tmp);
            }
            if (r + 1 < row) {
                int tmp = max(arr[r + 1][c], arr[r + 1][c + 1]);
                tmp = max(tmp, arr[r + 1][c + 2]);
                ret = max(ret, base + tmp);
            }
            if (c + 3 < col)
                ret = max(ret, base + arr[r][c + 3]);
        }
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int ans = 0;
    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> arr[i][j];
    loop(i, row) loop(j, col)
        ans = max(ans, nogada(i, j));
    cout << ans;
    return 0;
}
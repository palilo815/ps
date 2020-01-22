#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[100][100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, k;
    cin >> row >> col >> k;
    loop(i, row) loop(j, col)
        cin >> arr[i][j];

    int ans, min_cnt = 101;
    loop(i, row) {
        int dist = 0, cnt = 0;
        loop(j, col) {
            dist += arr[i][j];
            ++cnt;
            if (dist >= k) break;
        }
        if (dist >= k && cnt < min_cnt) {
            ans = i + 1;
            min_cnt = cnt;
        }
    }
    cout << ans << ' ' << min_cnt;
    return 0;
}
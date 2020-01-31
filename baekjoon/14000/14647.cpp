#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 500;

int nine[max_N][max_N];
int count_9(int num)
{
    int ret = 0;
    while (num) {
        if (num % 10 == 9) ++ret;
        num /= 10;
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    int total = 0;
    loop(i, row) loop(j, col) {
        int x; cin >> x;
        nine[i][j] = count_9(x);
        total += nine[i][j];
    }

    int ans = 0;
    loop(i, row) {
        int sum = 0;
        loop(j, col) sum += nine[i][j];
        if (sum > ans) ans = sum;
    }
    loop(i, col) {
        int sum = 0;
        loop(j, row) sum += nine[j][i];
        if (sum > ans) ans = sum;
    }
    cout << total - ans;
    return 0;
}
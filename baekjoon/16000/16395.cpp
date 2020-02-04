#include <iostream>
using namespace std;

int nCr[30][30];
int DP(int n, int r)
{
    if (r == 0 || n == r) return 1;
    int& ret = nCr[n][r];
    if (ret) return ret;
    return ret = DP(n - 1, r - 1) + DP(n - 1, r);
}
int main()
{
    int n, r; cin >> n >> r;
    cout << DP(n - 1, r - 1);
    return 0;
}
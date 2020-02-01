#include <bits/stdc++.h>
using namespace std;

int z_sum(int len, int r, int c)
{
    if (len == 1) return 2 * r + c;
    int half = len / 2;
    int ret = 0;
    if (r >= half) {
        r -= half;
        ret += 2 * pow(half, 2);
    }
    if (c >= half) {
        c -= half;
        ret += pow(half, 2);
    }
    return ret + z_sum(len / 2, r, c);
}

int main()
{
    int N, r, c;
    cin >> N >> r >> c;
    cout << z_sum(pow(2, N), r, c);
    return 0;
}
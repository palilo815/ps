#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;

long long Zsum(long long n, long long r, long long c)
{
    if (n == 1)
        return 2 * r + c;
    long long half_len = pow(2, n - 1);
    long long sum = 0;
    if (r >= half_len) {
        r -= half_len;
        sum += 2 * pow(half_len, 2);
    }
    if (c >= half_len) {
        c -= half_len;
        sum += pow(half_len, 2);
    }
    return sum + Zsum(n - 1, r, c);
}

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    long long N, r, c;
    cin >> N >> r >> c;
    cout << Zsum(N, r, c);
    return 0;
}
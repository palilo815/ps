#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool sieve[1003002];
bool Palin(int n)
{
    int tmp = n, rev = 0;
    while (tmp) {
        rev *= 10;
        rev += tmp % 10;
        tmp /= 10;
    }
    if (n == rev) return true;
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    // 소수 먼저 구해놓고
    sieve[0] = sieve[1] = true;
    for (int i = 2; i < 1003002; ++i)
        if (!sieve[i])
            for (int j = 2 * i; j < 1003002; j += i)
                sieve[j] = true;
    // 소수이면서 팰린드롬인지 체크
    for (int i = n; ; ++i)
        if (!sieve[i] && Palin(i)) {
            cout << i;
            break;
        }
    return 0;
}
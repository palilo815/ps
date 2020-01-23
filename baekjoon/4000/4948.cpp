#include <iostream>
#define MAX_N 123456
using namespace std;

bool sieve[MAX_N * 2 + 1];
int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    sieve[0] = sieve[1] = true;
    for (int i = 2;i <= MAX_N;++i)
        if (!sieve[i])
            for (int j = 2 * i;j <= MAX_N * 2;j += i)
                sieve[j] = true;
    int n;
    while (1) {
        cin >> n;
        if (n == 0) break;
        int cnt = 0;
        for (int i = n + 1; i <= 2 * n; ++i)
            if (!sieve[i])
                ++cnt;
        cout << cnt << '\n';
    }
    return 0;
}
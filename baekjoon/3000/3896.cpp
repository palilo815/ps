#include <bits/stdc++.h>
#define MAX 1299710
using namespace std;

bool sieve[MAX];
int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    sieve[0] = sieve[1] = true;
    for (int i = 2;i < MAX;++i)
        if (!sieve[i])
            for (int j = i * 2;j < MAX;j += i)
                sieve[j] = true;

    int T; cin >> T;
    while (T--) {
        int k; cin >> k;
        if (!sieve[k]) cout << 0 << '\n';
        else {
            int low = k - 1, high = k + 1;
            while (sieve[low]) --low;
            while (sieve[high]) ++high;
            cout << high - low << '\n';
        }
    }
    return 0;
}
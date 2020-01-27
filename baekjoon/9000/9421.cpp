#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool sieve[1000001];
set<int> cache;
bool happy(int num) {
    cache.clear();
    cache.insert(num);
    while (num != 1) {
        int tmp = 0;
        while (num) {
            tmp += pow(num % 10, 2);
            num /= 10;
        }
        if (cache.find(tmp) != cache.end()) return false;
        cache.insert(tmp);
        num = tmp;
    }
    return true;
}
int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    sieve[0] = sieve[1] = true;
    int n; cin >> n;
    for (int i = 2; i <= n; ++i)
        if (!sieve[i])
            for (int j = i * 2;j <= n;j += i)
                sieve[j] = true;

    for (int i = 2;i <= n;++i)
        if (!sieve[i] && happy(i))
            cout << i << '\n';
    return 0;
}
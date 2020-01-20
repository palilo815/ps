#include <iostream>
using namespace std;

bool sieve[4000001];
int contains(int num, int key)
{
    while (num) {
        if (num % 10 == key) return 1;
        num /= 10;
    }
    return 0;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    sieve[0] = sieve[1] = true;
    for (int i = 2; i < 4000001; ++i)
        if (!sieve[i])
            for (int j = i * 2; j < 4000001; j += i)
                sieve[j] = true;
    int a, b, key, ans = 0;
    cin >> a >> b >> key;
    for (int i = a; i <= b; ++i)
        if (!sieve[i])
            ans += contains(i, key);
    cout << ans;
    return 0;
}
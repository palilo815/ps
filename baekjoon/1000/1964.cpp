#include<iostream>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    long long  step, count = 1, MOD = 45678;
    cin >> step;
    for (long long i = 1; i <= step; i++) {
        count += 3 * i + 1;
        count %= MOD;
    }
    cout << count;
    return 0;
}
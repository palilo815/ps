#include <iostream>
using namespace std;

bool sieve[10001];
int main() {
    sieve[0] = sieve[1] = true;
    int A, B; cin >> A >> B;
    for (int i = 2; i * i <= B; ++i) if (!sieve[i])
        for (int j = i * i; j <= B; j += i)
            sieve[j] = true;

    int sum = 0, _min = 0;
    for (int i = A; i <= B; ++i) if (!sieve[i]) {
        sum += i;
        if (!_min) _min = i;
    }

    if (sum) cout << sum << '\n' << _min;
    else cout << -1;
    return 0;
}
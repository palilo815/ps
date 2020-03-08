#include <iostream>
using namespace std;

const int mod = 1000000009;

int main() {
    int N; cin >> N;
    long long ans = 2;
    while (--N) {
        ans %= mod;
        ans = ans * 3;
    }
    cout << ans / 3;
    return 0;
}
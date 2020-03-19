#include <bits/stdc++.h>
using namespace std;

int f(int n) {
    int ret = 0;
    while (n) {
        ret += (n % 10) * (n % 10);
        n /= 10;
    }
    return ret;
}
int main() {
    int N; cin >> N;
    set<int> cache;
    while (N != 1 && cache.find(N) == cache.end()) {
        cache.insert(N);
        N = f(N);
    }
    cout << (N == 1 ? "HAPPY" : "UNHAPPY");
    return 0;
}
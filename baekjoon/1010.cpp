#include <algorithm>
#include <iostream>
using namespace std;

int cache[31][31];

int nCr(int n, int r) {
    if (n == r) return 1;
    if (r == 1) return n;
    int &ret = cache[n][r];
    if (ret != 0) return ret;
    return ret = nCr(n - 1, r) + nCr(n - 1, r - 1);
}
int main() {
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int T, west, east;
    cin >> T;
    while (T--) {
        cin >> west >> east;
        cout << nCr(east, west) << '\n';
    }
    return 0;
}
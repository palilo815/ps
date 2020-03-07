#include <bits/stdc++.h>
using namespace std;

int main() {
    int A, B; cin >> A >> B;
    int ans = 0;
    while (A > B) {
        if (A % 2) ++A;
        else A /= 2;
        ++ans;
    }
    cout << ans + B - A;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    int A1 = INT_MIN, A2 = INT_MAX;
    int B1 = INT_MIN, B2 = INT_MAX;
    while (N--) {
        int x, y; cin >> x >> y;
        A1 = max(A1, x + y);
        A2 = min(A2, x + y);
        B1 = max(B1, x - y);
        B2 = min(B2, x - y);
    }
    cout << max(A1 - A2, B1 - B2);
    return 0;
}
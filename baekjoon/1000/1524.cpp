#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;

        int x;
        int A = 0, B = 0;
        while (N--) {
            cin >> x;
            if (x > A) A = x;
        }
        while (M--) {
            cin >> x;
            if (x > B) B = x;
        }
        
        cout << (A >= B ? 'S' : 'B') << '\n';
    }
    return 0;
}
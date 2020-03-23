#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int r, g, b, rr, gg, bb;
    int R = 0, G = 0, B = 0;

    int N; cin >> N;
    while (N--) {
        cin >> r >> g >> b;
        rr = min(G, B) + r;
        gg = min(B, R) + g;
        bb = min(R, G) + b;
        R = rr, G = gg, B = bb;
    }
    cout << min({ R,G,B });
    return 0;
}
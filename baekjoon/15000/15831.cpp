#include <bits/stdc++.h>
using namespace std;

const int max_N = 300000;

char dol[max_N];
int b, w;

void mov(int& ptr, int val) {
    if (dol[ptr] == 'B') b += val;
    else w += val;
    ++ptr;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, B, W; cin >> N >> B >> W;
    for (int i = 0; i < N; ++i) cin >> dol[i];
    int ans = 0, l = 0, r = 0;
    while (r <= N) {
        if (b > B) mov(l, -1);
        else {
            if (w >= W) ans = max(ans, r - l);
            mov(r, 1);
        }
    }
    cout << ans;
    return 0;
}
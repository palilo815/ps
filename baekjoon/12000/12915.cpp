#include <bits/stdc++.h>
using namespace std;

int main() {
    int E, EM, M, MH, H;
    cin >> E >> EM >> M >> MH >> H;

    int ans = min({E, M, H});
    E -= ans, M -= ans, H -= ans;

    for (int e, h;; ++ans) {
        e = h = 0;
        if (E) ++e, --E;
        else if (EM) ++e, --EM;

        if (H) ++h, --H;
        else if (MH) ++h, --MH;

        if (!e || !h || EM + M + MH == 0) break;
        if (M) --M;
        else EM > MH ? --EM : --MH;
    }
    cout << ans;
    return 0;
}
#include<bits/stdc++.h>
using namespace std;

bool leak[1001];
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, L; cin >> N >> L;
    while (N--) {
        int x; cin >> x;
        leak[x] = true;
    }

    int ans = 0;
    for (int i = 1; i <= 1000; ++i) if (leak[i]) {
        ++ans;
        for (int j = i + 1; j < i + L && j <= 1000; ++j)
            leak[j] = false;
    }
    cout << ans;
    return 0;
}
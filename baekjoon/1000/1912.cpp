#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, s; cin >> N >> s;
    int ans = s;
    for (int x; --N;) {
        cin >> x;
        s = s < 0 ? x : (s + x);
        if (s > ans) ans = s;
    }
    cout << ans;
    return 0;
}
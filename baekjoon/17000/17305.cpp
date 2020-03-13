#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<int> three, five;
    int N, W; cin >> N >> W;
    while (N--) {
        int w, s; cin >> w >> s;
        if (w == 3) three.emplace_back(s);
        else five.emplace_back(s);
    }

    sort(three.begin(), three.end(), greater<int>());
    sort(five.begin(), five.end(), greater<int>());
    
    ll ans = 0;
    auto it3 = three.begin();
    while (it3 != three.end() && W >= 3) {
        W -= 3;
        ans += *(it3++);
    }
    auto it5 = five.begin();
    while (it5 != five.end() && W >= 5) {
        W -= 5;
        ans += *(it5++);
    }

    ll tmp = ans;
    while (it3 != three.begin() && it5 != five.end()) {
        W += 3;
        tmp -= *(--it3);
        if (W >= 5) {
            W -= 5;
            tmp += *(it5++);
            ans = max(ans, tmp);
        }
    }
    cout << ans;
    return 0;
}
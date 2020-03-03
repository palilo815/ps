#include <bits/stdc++.h>
using namespace std;


int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    string num, ans;
    cin >> num;
    for (char c : num) {
        while (K && !ans.empty() && ans.back() < c) {
            ans.pop_back();
            --K;;
        }
        ans += c;
    }
    while (K--) ans.pop_back();
    cout << ans;
    return 0;
}
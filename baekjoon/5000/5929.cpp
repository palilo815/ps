#include <bits/stdc++.h>
using namespace std;

string to_3(int n) {
    string ret;
    for (; n; n /= 3)
        ret += '0' + n % 3;
    reverse(ret.begin(), ret.end());
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    unordered_set<string> st;

    string b2, b3; cin >> b2 >> b3;
    for (char& c : b3) {
        char prv = c;
        for (char nxt = '0'; nxt < '3'; ++nxt)
            if (prv ^ nxt) {
                c = nxt;
                st.emplace(b3);
            }
        c = prv;
    }

    int num = 0;
    for (char& c : b2) {
        num <<= 1;
        num += c == '1';
    }

    for (int i = 0; i < b2.size(); ++i) {
        int ans = num ^ (1 << i);
        if (st.count(to_3(ans))) {
            cout << ans;
            break;
        }
    }
    return 0;
}
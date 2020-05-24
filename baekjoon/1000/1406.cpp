#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    stack<char> L, R;
    string s; cin >> s;
    for (char c : s) L.emplace(c);

    int N; cin >> N;
    while (N--) {
        char c; cin >> c;
        switch (c) {
        case 'L':
            if (L.empty()) break;
            c = L.top(); L.pop();
            R.emplace(c);
            break;
        case 'D':
            if (R.empty()) break;
            c = R.top(); R.pop();
            L.emplace(c);
            break;
        case 'B':
            if (L.empty()) break;
            L.pop();
            break;
        case 'P':
            cin >> c;
            L.emplace(c);
        }
    }

    vector<char> ans;
    while (!L.empty()) {
        ans.emplace_back(L.top()); L.pop();
    }
    for (auto it = ans.rbegin(); it != ans.rend(); ++it)
        cout << *it;
    while (!R.empty()) {
        cout << R.top(); R.pop();
    }
    return 0;
}
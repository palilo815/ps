#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    string s;
    cin >> s;
    if (s.find('A') != string::npos) {
        replace_if(
            s.begin(), s.end(), [&](const auto& x) {
                return x == 'B' || x == 'C' || x == 'D' || x == 'F';
            },
            'A');
    }
    if (s.find('A') == string::npos && s.find('B') != string::npos) {
        replace_if(
            s.begin(), s.end(), [&](const auto& x) {
                return x == 'C' || x == 'D' || x == 'F';
            },
            'B');
    }
    if (s.find('A') == string::npos && s.find('B') == string::npos, s.find('C') != string::npos) {
        replace_if(
            s.begin(), s.end(), [&](const auto& x) {
                return x == 'D' || x == 'F';
            },
            'C');
    }
    if (s.find('A') == string::npos && s.find('B') == string::npos && s.find('C') == string::npos) {
        fill(s.begin(), s.end(), 'A');
    }
    cout << s;
}
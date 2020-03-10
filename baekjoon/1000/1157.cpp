#include <iostream>
using namespace std;

int cnt[26];
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    for (char c : s) {
        int i = (c >= 'a' ? c - 'a' : c - 'A');
        ++cnt[i];
    }
    int ans = 0;
    bool dup = false;
    for (int i = 1; i < 26; ++i) {
        if (cnt[i] > cnt[ans])
            ans = i, dup = false;
        else if (cnt[i] == cnt[ans])
            dup = true;
    }
    if (dup) cout << '?';
    else cout << (char)(ans + 'A');
    return 0;
}
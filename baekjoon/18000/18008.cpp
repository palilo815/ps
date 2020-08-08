#include <bits/stdc++.h>
using namespace std;

const int dist[26] = {1, 3, 3, 5, 5, 5, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11};
int cnt[26];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    string s; getline(cin, s);
    for (char& c : s) {
        if ('a' <= c && c <= 'z') ++cnt[c - 'a'];
        if ('A' <= c && c <= 'Z') ++cnt[c - 'A'];
    }

    sort(cnt, cnt + 26, greater<int>());
    int ans = accumulate(cnt, cnt + 26, -1) * 3;
    for (int i = 0; i < 26; ++i)
        ans += cnt[i] * dist[i];
    cout << ans;
    return 0;
}
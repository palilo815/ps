#include <bits/stdc++.h>
using namespace std;

set<string> cache;
string rev(string& s, int l, int r) {
    string ret = s;
    while (l < r) swap(ret[l++], ret[r--]);
    return ret;
}
int main() {
    int N, K; cin >> N >> K;
    string src = "", dst = "";
    for (int i = 1; i <= N; ++i) {
        char x; cin >> x;
        src += x;
        dst += to_string(i);
    }
    cache.insert(src);
    
    queue<string> q;
    q.push(src); q.push("");
    int ans = 0;
    while (1) {
        string u = q.front(); q.pop();
        if (u == "") {
            if (q.empty()) {
                ans = -1; break;
            }
            ++ans; q.push("");
            continue;
        }
        if (u == dst) break;

        for (int i = 0; i + K <= N; ++i) {
            string v = rev(u, i, i + K - 1);
            if (cache.find(v) == cache.end()) {
                cache.insert(v);
                q.push(v);
            }
        }
    }
    cout << ans;
    return 0;
}
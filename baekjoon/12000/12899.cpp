#include <bits/stdc++.h>
using namespace std;

const int sgX = 2097152;

int bit[sgX + 1];

void update(int i) {
    for (; i <= sgX; i += i & -i)
        ++bit[i];
}
void query(int k) {
    int s = 0;
    for (int len = sgX >> 1; len; len >>= 1)
        bit[s | len] < k ? (k -= bit[s |= len]) : --bit[s | len];
    cout << s + 1 << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, x;
    char q;

    cin >> n;
    while (n--) {
        cin >> q >> x;
        q == '1' ? update(x) : query(x);
    }
}
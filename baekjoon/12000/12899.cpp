#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;

const int sgN = 2097152;

int segT[sgN << 1];

void update(int i) {
    ++segT[i += sgN];
    while (i >>= 1)
        ++segT[i];
}
void query(int k) {
    int i = 1;
    while (i < sgN) {
        --segT[i];
        if (segT[left] >= k) i = left;
        else {
            k -= segT[left];
            i = right;
        }
    }
    --segT[i];
    cout << i - sgN << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    char q;
    int x;
    while (N--) {
        cin >> q >> x;
        q == '1' ? update(x) : query(x);
    }
    return 0;
}
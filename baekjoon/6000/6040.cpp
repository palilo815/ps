#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    int len = s.size();
    vector<int> vt(2 * len);
    loop(i, len) {
        int pos = len - 1 - i, val;
        if (s[pos] <= '9') val = s[pos] - '0';
        else val = s[pos] - 'A' + 10;
        int ex = 4 * i;
        vt[ex / 3] += pow(2, ex % 3) * val;
    }
    loop(i, 2 * len)
        if (vt[i] > 7) {
            vt[i + 1] += vt[i] / 8;
            vt[i] %= 8;
        }

    while (vt.back() == 0 && vt.size() != 1) vt.pop_back();
    auto it = vt.end();
    while (it != vt.begin()) cout << *--it;
    return 0;
}
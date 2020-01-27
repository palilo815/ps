#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string a, b; cin >> b;
    a = "0" + b + "0000";
    for (int i = a.size() - 1, j = b.size() - 1; i > 0; --i, --j) {
        int add = 0;
        if (j >= 0) add = b[j] - '0';
        a[i] += add;
        if (a[i] > '1') {
            a[i] -= 2;
            ++a[i - 1];
        }
    }
    int pos = 0;
    if (a[0] == '0') ++pos;
    while (pos < a.size()) cout << a[pos++];
    return 0;
}
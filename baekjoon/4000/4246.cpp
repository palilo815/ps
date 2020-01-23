#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    string s;
    while (cin >> n) {
        if (n == 0) break;
        cin >> s;
        loop(i, n) {
            int pos = i;
            bool f = true;
            while (pos < s.size()) {
                cout << s[pos];
                if (f) pos += 2 * n - 2 * i - 1;
                else pos += 2 * i + 1;
                f = !f;
            }
        }
        cout << '\n';
    }
    return 0;
}
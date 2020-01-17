#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, count[8];
    cin >> T;
    while (T--) {
        memset(count, 0, sizeof(count));
        string s; cin >> s;
        loop(i, 38) {
            int n = 0;
            if (s[i] == 'H') n += 4;
            if (s[i + 1] == 'H') n += 2;
            if (s[i + 2] == 'H') n += 1;
            ++count[n];
        }
        loop(i, 8)
            cout << count[i] << ' ';
        cout << '\n';
    }
    return 0;
}
#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (getline(cin, s)) {
        if (s == "#") break;
        int prev = -1, e = s.size();
        loop(i, e)
            if (s[i] == ' ') {
                for (int j = i - 1; j > prev; --j)
                    cout << s[j];
                cout << ' ';
                prev = i;
            }
        for (int j = e - 1; j > prev; --j)
            cout << s[j];
        cout << '\n';
    }
    return 0;
}
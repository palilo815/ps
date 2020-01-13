#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    cin.ignore();
    string s;
    while (T--) {
        getline(cin, s);
        int x = 0;
        loop(i, s.size()) {
            if (s[i] == 'g' || s[i] == 'G') x++;
            else if (s[i] == 'b' || s[i] == 'B') x--;
        }
        cout << s << " is ";
        if (x > 0) cout << "GOOD\n";
        else if (x < 0) cout << "A BADDY\n";
        else cout << "NEUTRAL\n";
    }
    return 0;
}
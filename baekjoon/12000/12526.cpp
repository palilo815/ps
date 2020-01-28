#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    char Mo[10] = { 'a','e','i','o','u','A','E','I','O','U' };
    string s;
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> s;
        cout << "Case #" << i << ": " << s << " is ruled by ";
        char L = s.back();
        if (L == 'y' || L == 'Y') cout << "nobody.\n";
        else {
            bool moum = false;
            loop(k, 10)
                if (L == Mo[k]) moum = true;
            if (moum) cout << "a queen.\n";
            else cout << "a king.\n";
        }
    }
    return 0;
}
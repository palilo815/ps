#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);

    int k, Len;
    cin >> k >> Len; cin.ignore();
    k = 26 - (k % 26);
    string s;
    getline(cin, s);
    loop(i, Len) {
        char c = s[i];
        if (c >= 'A' && c <= 'Z') {
            c -= k;
            if (c < 'A') c += 26;
        }
        else if (c >= 'a' && c <= 'z') {
            c -= k;
            if (c < 'a') c += 26;
        }
        cout << c;
    }
    return 0;
}
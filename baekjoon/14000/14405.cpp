#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    int len = s.size();
    bool flag = true;
    loop(i, len) {
        if (s[i] == 'p' && s[i + 1] == 'i') ++i;
        else if (s[i] == 'k' && s[i + 1] == 'a') ++i;
        else if (s[i] == 'c' && s[i + 1] == 'h' && s[i + 2] == 'u') i += 2;
        else {
            flag = false;
            break;
        }
    }
    if (flag) cout << "YES";
    else cout << "NO";
    return 0;
}
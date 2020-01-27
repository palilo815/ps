#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (1) {
        getline(cin, s);
        if (s == "*") break;

        char key = s[0];
        if (key > 'Z') key -= 32;
        bool Tau = true;
        loop(i, s.size())
            if (s[i] == ' ' && s[i + 1] != key && s[i + 1] != key + 32) {
                Tau = false;
                break;
            }

        if (Tau) cout << "Y\n";
        else cout << "N\n";
    }
    return 0;
}
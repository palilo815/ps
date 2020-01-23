#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char Mo[6] = { 'a', 'i', 'y', 'e', 'o', 'u' };
char Ja[20] = { 'b', 'k', 'x', 'z', 'n', 'h', 'd', 'c', 'w', 'g', 'p', 'v', 'j', 'q', 't', 's', 'r', 'l', 'm', 'f' };

char Conv(char c)
{
    loop(i, 6)
        if (Mo[i] == c) return Mo[(i + 3) % 6];
    loop(i, 20)
        if (Ja[i] == c) return Ja[(i + 10) % 20];
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (getline(cin, s)) {
        int L = s.length();
        loop(i, L) {
            char c = s[i];
            if (c >= 'A' && c <= 'Z')
                c = Conv(c + 32) - 32;
            else if (c >= 'a' && c <= 'z')
                c = Conv(c);
            cout << c;
        }
        cout << '\n';
    }
    return 0;
}
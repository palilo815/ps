#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string new_alph[26] = { "@","8","(","|)","3","#","6","[-]","|","_|","|<","1","[]\\/[]","[]\\[]","0","|D","(,)","|Z","$","']['","|_|","\\/","\\/\\/","}{","`/","2" };

    string s; getline(cin, s);
    for (char c : s) {
        if (c >= 'a' && c <= 'z') cout << new_alph[c - 'a'];
        else if (c >= 'A' && c <= 'Z') cout << new_alph[c - 'A'];
        else cout << c;
    }
    return 0;
}
#include<bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (getline(cin, s)) {
        if (s == "***") break;
        reverse(s.begin(), s.end());
        cout << s << '\n';
    }
    return 0;
}
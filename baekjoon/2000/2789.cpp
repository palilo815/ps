#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s; cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] != 'C' && s[i] != 'A' && s[i] != 'M' && s[i] != 'B' && s[i] != 'R' && s[i] != 'I' && s[i] != 'D' && s[i] != 'G' && s[i] != 'E')
            cout << s[i];
    }
    return 0;
}
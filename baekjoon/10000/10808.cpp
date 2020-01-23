#include <iostream>
using namespace std;

int main()
{
    string s; cin >> s;
    int cnt[26] = {};
    for (char c : s)
        ++cnt[c - 'a'];
    for (int i = 0;i < 26;++i)
        cout << cnt[i] << ' ';
    return 0;
}
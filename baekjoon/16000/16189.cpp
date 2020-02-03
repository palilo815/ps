#include <iostream>
using namespace std;

string pallin(string& s)
{
    int lt = 0, rt = s.size() - 1;
    while (lt < rt)
        if (s[lt++] != s[rt--]) return "NO";
    return "YES";
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // int는 아예 받지도 않는다.
    // k번 반복되건 말건 s가 pallindrome인지만 판별하면 된다.
    string s; cin >> s;
    cout << pallin(s);
    return 0;
}
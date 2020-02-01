#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    for (char x : s)
        cout << char(x - 'a' + 'A');
    return 0;
}
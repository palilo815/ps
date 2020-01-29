#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int len;
    string s;
    cin >> len >> s;

    bool linked = true;
    for(int i=1;i<2*len;++i)
        if (s[i] == s[i - 1]) {
            linked = false;
            break;
        }

    if (linked) cout << "Yes";
    else cout << "No";
    return 0;
}
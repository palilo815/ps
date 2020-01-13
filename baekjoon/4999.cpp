#include<iostream>
using namespace std;
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string a, b;
    cin >> a >> b;
    if (a.length() < b.length()) cout << "no";
    else cout << "go";
    return 0;
}
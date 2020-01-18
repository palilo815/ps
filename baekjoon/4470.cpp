#include<iostream>
#include<string>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int t; cin >> t;
    cin.ignore();
    string s;
    for (int i = 1; i <= t; i++) {
        getline(cin, s);
        cout << i << ". ";
        cout << s << '\n';
    }
    return 0;
}
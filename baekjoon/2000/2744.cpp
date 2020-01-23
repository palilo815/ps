#include<iostream>
using namespace std;

int main()
{
    string s; cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] < 'a') cout << (char)(s[i] + 32);
        else cout << (char)(s[i] - 32);
    }
    return 0;
}
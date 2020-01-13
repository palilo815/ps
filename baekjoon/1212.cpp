#include<iostream>
#include<string>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    string s;
    int First[8] = { 0,1,10,11,100,101,110,111 };
    string arr[8] = { "000","001","010","011","100","101","110","111" };

    cin >> s;
    for (int i = 0;i < s.length();i++) {
        if (i != 0)
            cout << arr[s[i] - '0'];
        else
            cout << First[s[i] - '0'];
    }
    return 0;
}
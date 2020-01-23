#include<iostream>
using namespace std;

int main()
{
    int DAY[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int m, d; cin >> d >> m;
    for (int i = 1;i < m;++i)
        d += DAY[i - 1];
    d %= 7;
    string s[7] = { "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday" };
    cout << s[d];
    return 0;
}
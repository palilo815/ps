#include<iostream>
#include <math.h>
using namespace std;

long long Conv(string s)
{
    if (s == "black") return 0;
    else if (s == "brown") return 1;
    else if (s == "red") return 2;
    else if (s == "orange") return 3;
    else if (s == "yellow") return 4;
    else if (s == "green") return 5;
    else if (s == "blue") return 6;
    else if (s == "violet") return 7;
    else if (s == "grey") return 8;
    else return 9;
}

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    long long a, b, c;
    string s;
    cin >> s;
    a = Conv(s);
    cin >> s;
    b = Conv(s);
    cin >> s;
    c = Conv(s);
    a = (10 * a + b) * pow(10, c);
    cout << a;
    return 0;
}
#include <iostream>
using namespace std;

int main()
{
    int n = 9;
    char c = 'F';
    int year, pres = 2013;
    cin >> year;
    if (year > pres) while (year != pres) {
        pres++, n++, c++;
        if (n == 10) n = 0;
        if (c == 'M') c = 'A';
    }
    else while (year != pres) {
        pres--, n--, c--;
        if (n == -1) n = 9;
        if (c == 64) c = 'L';
    }
    cout << c << n;
    return 0;
}
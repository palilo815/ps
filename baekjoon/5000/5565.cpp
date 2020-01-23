#include<iostream>
using namespace std;

int main()
{
    int sum, book, t = 9;
    cin >> sum;
    while (t--) {
        cin >> book;
        sum -= book;
    }
    cout << sum;
    return 0;
}
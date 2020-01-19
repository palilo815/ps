#include<iostream>
using namespace std;

int main()
{
    int n;
    for (int i = 1;;++i) {
        cin >> n;
        if (n == 0) break;
        cout << i << ". ";
        n *= 3;
        if (n % 2 == 0) {
            cout << "even ";
            n /= 2;
        }
        else {
            cout << "odd ";
            n = (n + 1) / 2;
        }
        n *= 3;
        cout << n / 9 << '\n';
    }
    return 0;
}
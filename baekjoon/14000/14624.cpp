#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    if (n % 2 == 0) cout << "I LOVE CBNU";
    else {
        cout << string(n, '*') << '\n';
        int a = n / 2, b = 1;
        cout << string(a--, ' ') << '*' << '\n';
        for (a; a >= 0; --a, b += 2)
            cout << string(a, ' ') << '*' << string(b, ' ') << '*' << '\n';
    }
    return 0;
}
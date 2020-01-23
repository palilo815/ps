#include <iostream>
using namespace std;

int main()
{
    int n, k, x; cin >> n >> k;
    while (k--) {
        cin >> x;
        n -= (x + 1) / 2;
    }
    if (n > 0) cout << "NO";
    else cout << "YES";
    return 0;
}
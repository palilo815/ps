#include<iostream>
using namespace std;

int main()
{
    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0) --k;
        if (k == 0) {
            cout << i;
            return 0;
        }
    }
    cout << 0;
    return 0;
}
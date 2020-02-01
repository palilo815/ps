#include <iostream>
using namespace std;
const int mod = 1000000007;

int main()
{
    int N; cin >> N;
    int a = 0, b = 1, tmp;
    for (int i = 2; i <= N;i++) {
        tmp = b;
        b = (a + b) % mod;
        a = tmp;
    }
    if (N == 0) b = 0;
    cout << b;
    return 0;
}
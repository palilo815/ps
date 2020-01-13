#include<iostream>
#include<algorithm>
using namespace std;

long long cache[2][91] = {};
long long Yichin(int prev, int n)
{
    if (n == 1) {
        if (prev == 0) return 2;
        else return 1;
    }
    long long& ret = cache[prev][n];
    if (ret != 0) return ret;
    if (prev == 0) return ret = Yichin(1, n - 1) + Yichin(0, n - 1);
    else return ret = Yichin(0, n - 1);
}

int main()
{
    int n;
    cin >> n;
    if (n == 1) cout << '1';
    else cout << Yichin(1, n - 1);
    return 0;
}
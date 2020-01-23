#include<iostream>
using namespace std;
int Sum(int n)
{
    int ret = 0;
    while (n) {
        ret += n % 10;
        n /= 10;
    }
    return ret;
}
int main()
{
    int n;
    while (1) {
        cin >> n;
        if (n == 0) break;
        while (n > 9) n = Sum(n);
        cout << n << '\n';
    }
    return 0;
}
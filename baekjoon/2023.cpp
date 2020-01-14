#include<iostream>
using namespace std;

int len;
bool IsPrime(int n)
{
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

// n으로 시작하는 l자리 소수를 만든다.
void makePrime(int n, int l)
{
    if (l == len) cout << n << '\n';
    n *= 10;
    for (int i = 1; i < 10; i += 2)
        if (IsPrime(n + i)) makePrime(n + i, l + 1);
}
int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    cin >> len;
    // 한 자리 소수는 2,3,5,7
    makePrime(2, 1);
    makePrime(3, 1);
    makePrime(5, 1);
    makePrime(7, 1);
    return 0;
}
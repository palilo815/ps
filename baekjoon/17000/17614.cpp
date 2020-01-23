#include <iostream>
using namespace std;

int clap(int num)
{
    int ret = 0;
    while (num) {
        if ((num % 10) && (num % 10) % 3 == 0) ++ret;
        num /= 10;
    }
    return ret;
}

int main()
{
    int N, ans = 0;
    cin >> N;
    for (int i = 1;i <= N;++i)
        ans += clap(i);
    cout << ans;
    return 0;
}
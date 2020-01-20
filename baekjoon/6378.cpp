#include <iostream>
using namespace std;

int digital_root(int n)
{
    int ret = 0;
    while (n) {
        ret += n % 10;
        n /= 10;
    }
    if (ret < 10) return ret;
    return digital_root(ret);
}
int main()
{
    int n;
    while (1) {
        cin >> n;
        if (n == 0) break;
        cout << digital_root(n) << '\n';
    }
    return 0;
}
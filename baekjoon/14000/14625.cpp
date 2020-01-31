#include <iostream>
using namespace std;

bool check(int n, int key)
{
    return (n / 10 == key || n % 10 == key);
}
int main()
{
    int h, m, H, M, key, ans = 0;
    cin >> h >> m >> H >> M >> key;
    while (1) {
        if (check(h, key) || check(m, key)) ++ans;
        if (h == H && m == M) break;
        ++m;
        if (m >= 60) m = 0, ++h;
    }
    cout << ans;
    return 0;
}
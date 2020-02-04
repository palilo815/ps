#include <iostream>
using namespace std;

int main()
{
    double sum = 0;
    int n; cin >> n;
    for (int i = 0;i < n;++i) {
        int scr; cin >> scr;
        if (scr == 100) { sum += 100; continue; }
        int a = scr / 10, b = scr % 10;
        if (a == 6) a = 9;
        if (b == 0 || b == 6) b = 9;
        sum += 10 * a + b;
    }
    cout << int(sum / n + 0.5);
    return 0;
}
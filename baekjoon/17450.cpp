#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    char name[3] = { 'S','N','U' };
    double price[3];
    loop(i, 3) {
        int c, w; cin >> c >> w;
        if (c >= 500) c -= 50;
        price[i] = 1.0 * w / c;
    }

    int idx = 2;
    loop(i, 2)
        if (price[i] > price[idx])
            idx = i;
    cout << name[idx];
    return 0;
}
#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    int l, r, a;
    cin >> l >> r >> a;
    int sum = l + r + a;
    int gap = abs(l - r);
    if (gap < a) cout << sum - ((a - gap) % 2);
    else cout << sum - gap + a;
    return 0;
}
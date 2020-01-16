#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    int a[5], sum = 0;
    for (int i = 0; i < 5; i++) {
        cin >> a[i];
        sum += a[i];
    }
    sort(a, a + 5);
    cout << sum / 5 << '\n' << a[2];
    return 0;
}
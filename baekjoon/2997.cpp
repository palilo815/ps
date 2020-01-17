#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int a[3];
    loop(i, 3) cin >> a[i];
    sort(a, a + 3);
    int gap1 = a[1] - a[0], gap2 = a[2] - a[1];
    if (gap1 == gap2)
        cout << a[2] + gap2;
    else {
        int num = (gap1 < gap2) ? a[1] + gap1 : a[1] - gap2;
        cout << num;
    }
    return 0;
}
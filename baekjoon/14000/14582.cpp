#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int a[9], b[9];
    loop(i, 9) cin >> a[i];
    loop(i, 9) cin >> b[i];

    bool leading = false;
    int scr = 0;
    loop(i, 9) {
        scr += a[i];
        if (scr > 0) leading = true;
        scr -= b[i];
    }
    if (leading) cout << "Yes";
    else cout << "No";
    return 0;
}
#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int req[32];
int main()
{
    int n; cin >> n;
    while (n--) {
        int a, b; cin >> a >> b;
        for (int i = a; i < b; ++i)
            ++req[i];
    }
    cin >> n;
    loop(i, 32)
        if (req[i] > n) {
            cout << 0;
            return 0;
        }
    cout << 1;
    return 0;
}
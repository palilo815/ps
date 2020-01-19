#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int n = 0, x;
    loop(i, 5) {
        cin >> x;
        n += x;
    }
    cout << n;
    return 0;
}
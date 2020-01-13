#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int k, A = 1, B = 0;
    cin >> k;
    while (k--) {
        int tmp = A;
        A += B;
        B += tmp;
        A -= tmp;
    }
    cout << A << " " << B;
    return 0;
}
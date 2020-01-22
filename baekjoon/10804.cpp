#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int card[20];
    loop(i, 20) card[i] = i + 1;
    loop(i, 10) {
        int a, b; cin >> a >> b;
        reverse(card + a - 1, card + b);
    }
    loop(i, 20) cout << card[i] << ' ';
    return 0;
}
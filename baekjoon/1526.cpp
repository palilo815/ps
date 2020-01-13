#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool all47(int n)
{
    while (n) {
        int tmp = n % 10;
        if (tmp != 4 && tmp != 7)
            return false;
        n /= 10;
    }
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    while (!all47(n)) --n;
    cout << n;
    return 0;
}
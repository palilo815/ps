#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int s, v1, v2;
    cin >> s >> v1 >> v2;
    for (int i = s / v1; i >= 0; --i) {
        int rem_s = s - i * v1;
        if (rem_s % v2 == 0) {
            cout << i << ' ' << rem_s / v2;
            return 0;
        }
    }
    cout << "Impossible";
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    bool cup[3] = { true, };
    int t, a, b;
    cin >> t;
    while (t--) {
        cin >> a >> b;
        swap(cup[a - 1], cup[b - 1]);
    }
    loop(i, 3)
        if (cup[i]) cout << i + 1;
    return 0;
}
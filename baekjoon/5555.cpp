#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string key, ring;
    int N, ans = 0;
    cin >> key >> N;
    while (N--) {
        cin >> ring;
        ring += ring;
        if (ring.find(key)) ++ans;
    }
    cout << ans;
    return 0;
}
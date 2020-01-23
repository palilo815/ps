#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int bird, song = 1, ans = 0;
    cin >> bird;
    while (bird) {
        if (song > bird)
            song = 1;
        bird -= song++;
        ++ans;
    }
    cout << ans;
    return 0;
}
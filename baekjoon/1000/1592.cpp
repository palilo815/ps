#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int num[1000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m, l;
    cin >> n >> m >> l;
    num[0] = 1;
    int curr = 0, ans = 0;
    while (num[curr] != m) {
        if (num[curr] % 2) curr = (curr + l) % n;
        else curr = (curr - l + n) % n;
        ++num[curr], ++ans;
    }
    cout << ans;
    return 0;
}
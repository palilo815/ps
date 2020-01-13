#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cnt[26];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    while (n--) {
        char c; cin >> c;
        ++cnt[c - 'a'];
    }
    char ans;
    int Max = 0;
    loop(i, 26)
        if (cnt[i] > Max) {
            Max = cnt[i];
            ans = i + 'a';
        }
    cout << ans << ' ' << Max;
    return 0;
}
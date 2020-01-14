#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cnt[4][50];
char ItoC[4] = { 'A','C','G','T' };
int CtoI(char c)
{
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, LEN;
    cin >> n >> LEN;
    loop(T, n) loop(i, LEN) {
        char c; cin >> c;
        ++cnt[CtoI(c)][i];
    }
    int ans = 0;
    loop(i, LEN) {
        int tmp = 0, idx;
        loop(k, 4)
            if (cnt[k][i] > tmp) {
                tmp = cnt[k][i];
                idx = k;
            }
        ans += n - tmp;
        cout << ItoC[idx];
    }
    cout << '\n' << ans;
    return 0;
}
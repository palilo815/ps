#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int Cache[2][31][1000];
int t, Tree[1000];
int DP(int Tr, int Mv, int Jadu)
{
    if (Jadu == t) return 0;
    int& ret = Cache[Tr][Mv][Jadu];
    if (ret != -1) return ret;
    if (Tree[Jadu] == Tr)
        return ret = 1 + DP(Tr, Mv, Jadu + 1);
    ret = DP(Tr, Mv, Jadu + 1);
    if (Mv > 0) ret = max(ret, DP(1 - Tr, Mv - 1, Jadu + 1) + 1);
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(Cache, -1, 2 * 31 * 1000 * 4);
    int w;
    cin >> t >> w;
    loop(i, t) {
        int x; cin >> x;
        Tree[i] = x & 1;
    }
    cout << DP(1, w, 0);
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

struct S {
    int num;
    int count;
    int appear;
};
bool Comp(S& a, S& b)
{
    if (a.count == b.count)
        return a.appear > b.appear;
    return a.count > b.count;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // c는 대체 왜 주는거지?
    int n, c; cin >> n >> c;
    vector<S> vt;
    while (n--) {
        int x; cin >> x;
        loop(i, vt.size())
            if (vt[i].num == x) {
                ++vt[i].count;
                goto OUT;
            }
        vt.push_back({ x,1,n });
    OUT:;
    }

    sort(vt.begin(), vt.end(), Comp);
    loop(i, vt.size()) {
        int len = vt[i].count, num = vt[i].num;
        while (len--) cout << num << ' ';
    }
    return 0;
}
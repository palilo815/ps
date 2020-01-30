#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;
const int max_N = 100;

P cow[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> cow[i].first >> cow[i].second;
    sort(cow, cow + n);

    int T = 0;
    loop(i, n) {
        if (cow[i].first > T) T = cow[i].first;
        T += cow[i].second;
    }
    cout << T;
    return 0;
}
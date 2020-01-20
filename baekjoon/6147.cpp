#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cow[20000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, h; cin >> n >> h;
    loop(i, n) cin >> cow[i];
    sort(cow, cow + n, greater<int>());
    int sum = 0, i = 0;
    while (sum < h) sum += cow[i++];
    cout << i;
    return 0;
}
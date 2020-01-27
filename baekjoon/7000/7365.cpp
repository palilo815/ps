#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    vector<pair<double, int>> ans;
    int a[3], b[7];
    loop(i, 3) scanf("%d", &a[i]);
    loop(i, 7) scanf("%d", &b[i]);
    loop(i, 3) loop(j, 7)
        ans.push_back(make_pair(1.0 * a[i] / b[j], 10 * i + j));
    sort(ans.begin(), ans.end());
    loop(i, 21)
        printf("%.2lf %d %d\n", ans[i].first, ans[i].second / 10 + 1, ans[i].second % 10 + 1);
    return 0;
}
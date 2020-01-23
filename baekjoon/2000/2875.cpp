#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int female, male, k, team = 0;
    cin >> female >> male >> k;

    while (female > 1 && male > 0)
        female -= 2, male--, team++;

    k -= (female + male);
    while (k > 0)
        team--, k -= 3;

    cout << team;
    return 0;
}
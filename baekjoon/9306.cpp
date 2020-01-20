#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T;
    cin >> T;
    string F, L;
    for (int t = 1; t <= T; ++t) {
        cin >> F >> L;
        cout << "Case " << t << ": " << L << ", " << F << '\n';
    }
    return 0;
}
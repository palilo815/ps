#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int score[101], target[100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m; cin >> n >> m;
    loop(i, m) cin >> target[i];
    loop(i, m) {
        int tmp = 0;
        for (int j = 1; j <= n; ++j) {
            int doubt; cin >> doubt;
            if (target[i] == doubt)
                ++score[j];
            else ++tmp;
        }
        score[target[i]] += tmp;
    }
    for (int i = 1; i <= n; ++i)
        cout << score[i] << '\n';
    return 0;
}
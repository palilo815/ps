#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int score[100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    int ans = 0;
    loop(i, N) cin >> score[i];
    for (int i = N - 2; i >= 0; --i) {
        if (score[i] >= score[i + 1]) {
            ans += score[i] - score[i + 1] + 1;
            score[i] = score[i + 1] - 1;
        }
    }
    cout << ans;
    return 0;
}
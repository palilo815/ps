#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 100;

int basket[max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    for (int i = 1; i <= N; ++i) basket[i] = i;
    while (M--) {
        int s, e, m;
        cin >> s >> e >> m;
        vector<int> tmp;
        for (int i = s; i < m; ++i) tmp.push_back(basket[i]);
        int gap = m - s, i;
        for (i = s; i <= s + e - m; ++i)
            basket[i] = basket[i + gap];
        for (int x : tmp)
            basket[i++] = x;
    }
    for (int i = 1; i <= N; ++i) cout << basket[i] << ' ';
    return 0;
}
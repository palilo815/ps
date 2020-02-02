#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<int> L, R;
    int N, M; cin >> N >> M;
    while (N--) {
        int x; cin >> x;
        if (x < 0) L.push_back(-x);
        else R.push_back(x);
    }

    sort(L.begin(), L.end(), greater<int>());
    sort(R.begin(), R.end(), greater<int>());
    int len_L = L.size(), len_R = R.size();

    // 가장 먼 곳을 방문할 때, 그 이전 M-1군데를 동시에 방문해야 최소값이 나온다.
    int ans = 0;
    loop(i, len_L)
        if (i % M == 0) ans += L[i];
    loop(i, len_R)
        if (i % M == 0) ans += R[i];

    // 책을 가지러 되돌아와야 하므로 ans*2를 해준다.
    // 그러나 맨 마지막에 놓을 때는 되돌아올 필요가 없다.
    // 가장 먼 곳에 있는 책은 되돌아오지 않는다.
    // 가장 먼 곳에 있는 책은 max(L[0],R[0])이다.
    cout << ans * 2 - max(L.empty() ? 0 : L[0], R.empty() ? 0 : R[0]);
    return 0;
}
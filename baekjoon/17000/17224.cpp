#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, L, K, ans = 0;
    cin >> N >> L >> K;

    // hard를 풀 수 있으면 140점을, easy만 풀 수 있으면 100점을 넣는다.
    vector<int> Q;
    while (N--) {
        int easy, hard; cin >> easy >> hard;
        if (L >= hard) Q.push_back(140);
        else if (L >= easy) Q.push_back(100);
    }

    // 정렬한 뒤, 앞의 K개만 더해서 출력한다.
    sort(Q.begin(), Q.end(), greater<int>());
    for (int i = 0; i < K && i < Q.size(); ++i)
        ans += Q[i];
    cout << ans;
    return 0;
}
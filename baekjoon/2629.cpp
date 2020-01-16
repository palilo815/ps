#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

// 측정 가능한 무게
bool weight[15001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    int range = 0; // 현재 만들 수 있는 최대 무게
    while (N--) {
        int w; cin >> w;
        vector<int> tmp;

        loop(i, range + 1)
            if (weight[i]) {
                // i를 만들 수 있으면
                // abs(i-w)와 i+w도 만들 수 있다.
                int next = abs(w - i);
                if (!weight[next]) tmp.push_back(next);
                next = w + i;
                if (!weight[next]) tmp.push_back(next);
            }

        range = max(range, w);
        if (!tmp.empty())
            range = max(range, tmp.back());

        weight[w] = true;
        for (int x : tmp)
            weight[x] = true;
    }
    vector<char> ans;
    cin >> N;
    while (N--) {
        int w; cin >> w;
        if (w > 15000) ans.push_back('N');
        else {
            if (weight[w]) ans.push_back('Y');
            else ans.push_back('N');
        }
    }
    for (char c : ans)
        cout << c << ' ';
    return 0;
}
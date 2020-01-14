#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 전략 : 
    // 음수는 음수끼리 곱한다.
    // 양수는 양수끼리 곱한다.
    // 단 1은 곱하지 않고 따로 더하는 것이 이득이다.
    // 단 0은 음수가 1개 남았을 경우, 여기에 곱해서 0으로 만들어주고
    // 남은 음수가 없을 경우, 따로 더해준다.
    vector<int> pos, neg;
    int n, Z = 0, O = 0; // Zero, One은 따로 세준다.
    cin >> n;
    while (n--) {
        int x; cin >> x;
        if (x == 0) ++Z;
        else if (x == 1) ++O;
        else if (x < 0) neg.push_back(x);
        else pos.push_back(x);
    }

    sort(neg.begin(), neg.end(), greater<int>());
    sort(pos.begin(), pos.end());

    ll score = 0;
    while (neg.size() >= 2) {
        ll tmp = neg.back(); neg.pop_back();
        tmp *= (ll)neg.back(); neg.pop_back();
        score += tmp;
    }
    while (pos.size() >= 2) {
        ll tmp = pos.back(); pos.pop_back();
        tmp *= (ll)pos.back(); pos.pop_back();
        score += tmp;
    }

    // 만약 음수가 남았는데, 상쇄해줄 0이 없다면 점수가 감소
    if (neg.size() == 1 && Z == 0) score += neg[0];
    // 짝이 없는 양수 따로 더함
    if (pos.size()) score += pos[0];
    // 1인 따로 더해준다.
    cout << score + O;
    return 0;
}
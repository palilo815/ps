#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

vector<int> Pay[10001];	//index날까지 강연해주면 받는 pay 목록
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    while (n--) {
        int p, d; cin >> p >> d;
        Pay[d].push_back(p);
    }
    int Ans = 0;
    priority_queue<int> pq;
    for (int i = 10000; i > 0; --i) {
        loop(j, Pay[i].size()) pq.push(Pay[i][j]);
        if (!pq.empty()) {
            Ans += pq.top();
            pq.pop();
        }
    }
    cout << Ans;
    return 0;
}
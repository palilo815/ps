#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    priority_queue<double> pq;
    int N; cin >> N;

    // 일단 7명을 넣는다.
    double d;
    for (int i = 0; i < 7; ++i) {
        cin >> d;
        pq.push(d);
    }

    // pq에 가장 낮은 점수 7개가 들어있도록 한다.
    N -= 7;
    while (N--) {
        cin >> d;
        if (pq.top() > d) {
            pq.pop();
            pq.push(d);
        }
    }

    // 거꾸로 stack에 넣은뒤 출력
    stack<double> ans;
    while (!pq.empty()) {
        ans.push(pq.top());
        pq.pop();
    }
    while (!ans.empty()) {
        cout << fixed << setprecision(3) << ans.top() << '\n';
        ans.pop();
    }
    return 0;
}
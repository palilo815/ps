#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<=n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, Dasom; cin >> n >> Dasom;
    int tmp = Dasom;    // 매수 전 득표수

    // 단일 후보일 경우
    if (n == 1) { cout << 0; return 0; }

    // pq에는 각 후보별 예상 득표수를 넣는다.
    priority_queue<int> pq;
    while (--n) {
        int Vote; cin >> Vote;
        pq.push(Vote);
    }

    // pq.top == 가장 많은 득표수
    // pq.top < Dasom이면 다솜이가 당선된다.
    // pq.top을 1씩 감소시켜준다.
    while (pq.top() >= Dasom) {
        int x = pq.top();
        pq.pop();
        ++Dasom;
        pq.push(x - 1);
    }
    cout << Dasom - tmp;
    return 0;
}
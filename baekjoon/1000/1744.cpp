#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    // 양수, 음수를 담는 pq
    priority_queue<int> pos;
    priority_queue<int, vector<int>, greater<int>> neg;

    int sum = 0, zero = 0;
    while (N--) {
        int n; cin >> n;
        if (n == 0) ++zero; // 0은 마지막에 사용됨
        else if (n == 1) ++sum; // 1은 안묶고 바로 더한다.
        else if (n > 0) pos.push(n);
        else neg.push(n);
    }

    // 양수에서 가장 큰 것들 2개씩 짝지어서 곱하고 더한다.
    while (pos.size() >= 2) {
        int tmp = pos.top(); pos.pop();
        tmp *= pos.top(); pos.pop();
        sum += tmp;
    }
    if (!pos.empty()) sum += pos.top();

    // 음수에서 가장 작은 것들 2개씩 짝지어서 곱하고 더한다.
    while (neg.size() >= 2) {
        int tmp = neg.top(); neg.pop();
        tmp *= neg.top(); neg.pop();
        sum += tmp;
    }
    // 만약 음수의 개수가 홀수면 답에 음수를 더해야 하는데,
    // 숫자 중에서 0이 있다면 이 음수에 곱해서 상쇄시킬 수 있다.
    // 하지만 음수도 남았는데, 0도 없다면 어쩔수없이 sum에 음수를 더해야함
    if (!neg.empty() && !zero)
        sum += neg.top();
    cout << sum;
    return 0;
}
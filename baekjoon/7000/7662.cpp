#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_k = 1000000;

// i번째 요소가 큐에 남아있어야 하는지 여부
bool valid[max_k];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        priority_queue<p> pq_max;
        priority_queue<p, vector<p>, greater<p>> pq_min;

        int k; cin >> k;
        fill(valid, valid + k, false);
        char inst; int x;
        for (int i = 0; i < k; ++i) {
            cin >> inst >> x;
            if (inst == 'I') {
                // x를 집어넣는다.
                // x는 i번째 instruction때 push되었다.
                // valid[i] = true (i번째 push된 값은 큐에 들어가있다.)
                valid[i] = true;
                pq_max.push({ x,i });
                pq_min.push({ x,i });
            }
            else {
                // pq에서 뺀다.
                // 빼고난 뒤 valid[i] = false로 바꿔준다.
                // 나중에 pq_max나 pq_min에서 i번 요소를 발견했다면,
                // 이것은 pq에서 이미 빠진 요소이므로 무시해야 한다.
                if (x == 1) while (!pq_max.empty()) {
                    auto idx = pq_max.top().second; pq_max.pop();
                    if (!valid[idx]) continue;
                    valid[idx] = false;
                    break;
                }
                else while (!pq_min.empty()) {
                    auto idx = pq_min.top().second; pq_min.pop();
                    if (!valid[idx]) continue;
                    valid[idx] = false;
                    break;
                }
            }
        }
        // 잔반 처리
        while (!pq_max.empty() && !valid[pq_max.top().second]) pq_max.pop();
        while (!pq_min.empty() && !valid[pq_min.top().second]) pq_min.pop();

        // 정답 출력
        if (pq_max.empty()) cout << "EMPTY\n";
        else cout << pq_max.top().first << ' ' << pq_min.top().first << '\n';
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define loop(i, n) for (int i = 0; i < n; ++i)

// key가 앞쪽에 가까우면 true;
// 뒤쪽에 가까우면 false
bool Front(int key, deque<int>& DQ) {
    auto it1 = DQ.begin(), it2 = DQ.end();
    it2--;
    while (1) {
        if (*it1 == key) return true;
        if (*it2 == key) return false;
        it1++, it2--;
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    deque<int> dq;
    int n, m, key, ans = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        dq.push_back(i);
    while (m-- > 0) {
        cin >> key;
        // 앞쪽에서 뽑는게 유리하면 앞에서 뽑고
        // 뒤가 유리하면 뒤에서 뽑는다.
        if (Front(key, dq)) {
            while (dq.front() != key) {
                int x = dq.front();
                dq.pop_front();
                dq.push_back(x);
                ans++;
            }
        }
        else {
            while (dq.front() != key) {
                int x = dq.back();
                dq.pop_back();
                dq.push_front(x);
                ans++;
            }
        }
        dq.pop_front();
    }
    cout << ans;
    return 0;
}
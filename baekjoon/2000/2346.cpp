#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    deque<P> dq;
    int N; cin >> N;
    loop(i, N) {
        int x; cin >> x;
        dq.push_back({ i + 1,x });
    }

    while (1) {
        int idx = dq.front().first, mov = dq.front().second;
        dq.pop_front();
        cout << idx << ' ';

        if (dq.empty()) break;
        if (mov > 0) {
            --mov;
            while (mov--) {
                P tmp = dq.front(); dq.pop_front();
                dq.push_back(tmp);
            }
        }
        else {
            mov = -mov;
            while (mov--) {
                P tmp = dq.back(); dq.pop_back();
                dq.push_front(tmp);
            }
        }
    }
    return 0;
}
#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    deque<int> dq;
    string order;
    int T; cin >> T;
    while (T--) {
        dq.clear();
        bool front = true, valid = true;
        int x, len; char c;
        cin >> order >> len >> c;
        while (len--) {
            cin >> x;
            dq.emplace_back(x);
            if (len) cin >> c;
        }
        cin >> c;

        for (char c : order) {
            if (c == 'R') front = !front;
            else {
                if (dq.empty()) {
                    valid = false;
                    break;
                }
                if (front) dq.pop_front();
                else dq.pop_back();
            }
        }

        if (!valid) {
            cout << "error\n";
            continue;
        }

        cout << '[';
        if (front) {
            auto s = dq.begin(), e = dq.end();
            while (s != e) {
                if (s != dq.begin()) cout << ',';
                cout << *s++;
            }
        }
        else {
            auto s = dq.rbegin(), e = dq.rend();
            while (s != e) {
                if (s != dq.rbegin()) cout << ',';
                cout << *s++;
            }
        }
        cout << "]\n";
    }
    return 0;
}
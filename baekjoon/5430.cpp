#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    deque<int> dq;
    string order;
    int T; cin >> T;
    while (T--) {
        dq.clear();

        // ** initialize **
        // 파싱해서 숫자만 dq에 집어넣는다.
        bool front = true, valid = true;
        int x, len; char c;
        cin >> order >> len >> c;
        while (len--) {
            cin >> x;
            dq.push_back(x);
            if (len) cin >> c;
        }
        cin >> c;

        for(char c : order) {
            // R : front만 바꿔준다.
            if (c == 'R') front = !front;

            // D : front일 경우 앞에서 빼고, front가 아닐 경우 뒤에서 뺀다.
            else {
                if (dq.empty()) {
                    valid = false;
                    break;
                }
                if (front) dq.pop_front();
                else dq.pop_back();
            }
        }

        // 유효한 order일 경우 정답 출력
        if (valid) {
            cout << '[';
            // front일 경우 앞->뒤로 출력
            if (front) {
                auto s = dq.begin(), e = dq.end();
                while (s != e) {
                    if (s != dq.begin()) cout << ',';
                    cout << *s++;
                }
            }
            // front가 아닐 경우 뒤->앞으로 출력
            else {
                auto s = dq.rbegin(), e = dq.rend();
                while (s != e) {
                    if (s != dq.rbegin()) cout << ',';
                    cout << *s++;
                }
            }
            cout << "]\n";
        }
        // error
        else cout << "error\n";
    }
    return 0;
}
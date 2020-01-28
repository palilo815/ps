#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 서있는 줄은 queue로,
    // 임시로 들어가는 공간은 stack으로 표현한다
    stack<int> stk; stk.push(-1);
    queue<int> q;

    int n; cin >> n;
    loop(i, n) {
        int x; cin >> x;
        q.push(x);
    }

    // num = 1부터 시작
    int num = 1;
    while (!q.empty()) {
        // case 1 : 줄 바로 앞에 있는 경우, 바로 받으면 된다.
        if (q.front() == num) {
            q.pop();
            ++num;
        }
        // case 2: 줄 바로 앞에 없는 경우, num을 찾는다.
        else {
            // case 2-1 : 임시공간에 num이 있는 경우 빼낸다.
            if (stk.top() == num) {
                stk.pop();
                ++num;
            }
            // case 2-2 : 다 해당이 안되면, num이 나올때까지 queue의 인원을 stack으로 옮긴다.
            else {
                stk.push(q.front());
                q.pop();
            }
        }
    }
    // 마무리 작업
    while (stk.top() == num) {
        stk.pop();
        ++num;
    }

    if (stk.top() == -1) cout << "Nice";
    else cout << "Sad";
    return 0;
}
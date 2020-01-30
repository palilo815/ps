#include <iostream>
#include <stack>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000000;

int h[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> h[i];
    stack<int> stk;
    for (int i = N - 1; i >= 0; --i) {
        // stack에 남아있는 값은 i보다 오른쪽에 있는 높이다.
        int height = h[i];
        while (!stk.empty() && stk.top() <= height)
            stk.pop();

        // h[] array를 정답 저장용으로 재사용한다.
        if (stk.empty()) h[i] = -1;
        else h[i] = stk.top();
        stk.push(height);
    }
    loop(i, N) cout << h[i] << ' ';
    return 0;
}
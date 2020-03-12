#include <bits/stdc++.h>
using namespace std;

int cnt[26];
char must_use(int N) {
    int max_i = 0;
    for (int i = 1; i < 26; ++i) if (cnt[i] > cnt[max_i])
        max_i = i;
    return (cnt[max_i] >= (N + 1) / 2 ? max_i + 'a' : '\n');
}
int main() {
    string s; cin >> s;
    sort(s.begin(), s.end());
    for (char c : s) ++cnt[c - 'a'];
    int N = s.size();

    // 불가능한 경우 미리 처리
    for (int i = 0; i < 26; ++i) if (cnt[i] > (N + 1) / 2) {
        cout << -1;
        return 0;
    }

    // 정답의 앞의 절반은 바로바로 출력하고
    // 뒤의 절반은 스택에 넣었다가 마지막에 출력한다.
    stack<char> ans;
    for (int i = 0; N > 1; ++i, N -= 2) {
        // 가장 유리한 경우는
        // 사전상 가장 앞인 문자를 앞에 두고
        // 가장 뒤인 문자를 뒤에 두는 걸 반복하면 된다.

        // 단 반드시 써야하는 문자가 있는 경우 따로 처리를 해야 한다.

        // ** 남은 문자열 중 가장 앞인 문자 s[i]
        cout << s[i];
        --cnt[s[i] - 'a'];

        char x = must_use(N);
        // 만약 반드시 써야하는 문자가 없거나, s[i]에서 이미 사용한 경우
        // 뒤의 문자는 아무거나 골라도 되므로, 가장 뒤의 문자를 사용한다.
        if (x == '\n' || s[i] == x) {
            --cnt[s.back() - 'a'];
            ans.push(s.back());
            s.pop_back();
        }
        // 반드시 써야하는 문자가 있고, s[i]가 아닌 경우
        // 뒤의 문자는 반드시 x가 되어야 한다.
        else {
            --cnt[x - 'a'];
            ans.push(x);
            size_t it = s.find(x);
            s.erase(it, 1);
        }
    }

    // N이 홀수면 남은거 출력
    if (N) for (int i = 0; i < 26; ++i) if (cnt[i])
        cout << (char)(i + 'a');

    // 스택에서 꺼내와 마무리
    while (!ans.empty()) {
        cout << ans.top();
        ans.pop();
    }
    return 0;
}
#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string a, b; cin >> a >> b;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    vector<int> ans(100);
    int len_a = a.size(), len_b = b.size();

    // a * b
    loop(i, len_b)
        // b에서 1을 발견하면 그 위치만큼 a를 shift한 뒤 ans에 더해준다.
        if (b[i] == '1')
            loop(j, len_a)
            ans[i + j] += a[j] - '0';
    // 자릿수 올림
    loop(i, 100)
        if (ans[i] > 1) {
            ans[i + 1] += ans[i] / 2;
            ans[i] %= 2;
        }

    // 첫 자리가 0이면 전부 제거하고 출력
    while (ans.back() == 0) ans.pop_back();
    for (auto it = ans.rbegin(); it != ans.rend(); ++it)
        cout << *it;
    return 0;
}
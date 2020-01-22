#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int stroke[26] = { 3,2,1,2,4,3,1,3,1,1,3,1,3,2,1,2,2,2,1,2,1,1,1,2,2,1 };
    int len_a, len_b;
    string a, b;
    cin >> len_a >> len_b >> a >> b;

    vector<int> ans;
    int i;
    for (i = 0; i < len_a && i < len_b; ++i) {
        ans.push_back(stroke[a[i] - 'A']);
        ans.push_back(stroke[b[i] - 'A']);
    }
    while (i < len_a)
        ans.push_back(stroke[a[i++] - 'A']);
    while (i < len_b)
        ans.push_back(stroke[b[i++] - 'A']);

    while (ans.size() > 2) {
        loop(j, ans.size() - 1) {
            ans[j] += ans[j + 1];
            ans[j] %= 10;
        }
        ans.pop_back();
    }

    int Goong = ans[0] * 10 + ans[1];
    cout << Goong << '%';
    return 0;
}
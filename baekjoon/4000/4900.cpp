#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

string num[10] = { "063", "010", "093", "079", "106", "103", "119", "011", "127", "107" };

// 10진수로 바꿔서 return
int conv(const string& s)
{
    int len = s.size(), ret = 0;
    for (int i = 0; i < len; i += 3) {
        string tmp = s.substr(i, 3);
        loop(i, 10)
            if (num[i] == tmp) {
                ret *= 10;
                ret += i;
                break;
            }
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (cin >> s) {
        if (s == "BYE") break;
        int pivot = 0, A, B, C;
        // pivot : +위치
        while (s[pivot] != '+') ++pivot;
        A = conv(s.substr(0, pivot));
        B = conv(s.substr(pivot + 1, s.size() - pivot - 2));
        // A, B를 10진수로 바꿔서 계산한다.
        C = A + B;

        stack<int> ans;
        while (C) {
            ans.push(C % 10);
            C /= 10;
        }
        cout << s;
        while (!ans.empty()) {
            cout << num[ans.top()];
            ans.pop();
        }
        cout << '\n';
    }
    return 0;
}
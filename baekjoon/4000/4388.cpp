#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int L1, L2;
    string s1, s2;
    while (cin >> s1 >> s2) {
        if (s1 == "0" && s2 == "0") break;
        // string으로 숫자를 받아서
        // n1, n2에 각 자릿수를 넣는다.
        vector<int> n1(11), n2(11);
        L1 = s1.length(), L2 = s2.length();
        loop(i, L1) n1[10 - i] = s1[L1 - 1 - i] - '0';
        loop(i, L2) n2[10 - i] = s2[L2 - 1 - i] - '0';

        // 자릿수끼리 더하면서 carry가 나오면 Ans 증가
        int Ans = 0;
        for (int i = 10; i >= 0; --i) {
            n1[i] += n2[i];
            if (n1[i] > 9) {
                Ans++;
                n1[i - 1]++;
            }
        }
        cout << Ans << '\n';
    }
    return 0;
}
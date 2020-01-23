#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    string s1, s2;
    cin >> s1 >> s2;
    int len = max(s1.length(), s2.length());
    int* num1 = new int[len + 1]{};
    int* num2 = new int[len + 1]{};
    int* ans = new int[len + 1]{};

    for (int i = 0; i < s1.length();i++)
        num1[i] = s1[s1.length() - 1 - i] - '0';
    for (int i = 0; i < s2.length();i++)
        num2[i] = s2[s2.length() - 1 - i] - '0';

    for (int i = 0; i < len + 1;i++) {
        ans[i] += num1[i] + num2[i];
        if (ans[i] > 1) {
            ans[i + 1]++;
            ans[i] -= 2;
        }
    }
    int index = -10;
    for (int i = len; i >= 0; i--) {
        if (ans[i] == 1) {
            index = i;
            break;
        }
    }
    if (index == -10)
        cout << '0';
    else {
        for (int i = index; i >= 0; i--)
            cout << ans[i];
    }
    return 0;
}
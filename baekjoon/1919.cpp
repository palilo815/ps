#include<iostream>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    string s1, s2;
    cin >> s1 >> s2;
    int alpha[2][26] = {};
    for (int i = 0; i < s1.length(); i++)
        alpha[0][s1[i] - 'a']++;
    for (int i = 0; i < s2.length(); i++)
        alpha[1][s2[i] - 'a']++;
    int ans = 0;
    for (int i = 0; i < 26; i++)
        ans += abs(alpha[0][i] - alpha[1][i]);
    cout << ans;
    return 0;
}
#include<iostream>
#include<string>
using namespace std;


int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int n; cin >> n;
    while (n--) {
        cin >> s;
        bool flag = true;
        int table[26] = {};
        for (int i = 0; i < s.size();++i) {
            int index = s[i] - 'A';
            ++table[index];
            if (table[index] == 3) {
                if (s[i + 1] == s[i])
                    ++i;
                else {
                    flag = false;
                    break;
                }
                table[index] = 0;
            }
        }
        if (flag) cout << "OK\n";
        else cout << "FAKE\n";
    }
    return 0;
}
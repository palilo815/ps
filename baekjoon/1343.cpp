#include<iostream>
#include<algorithm>
#include<vector>
#include<iterator>
#include<string>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int numofx = 0;
    vector<char> ans;
    string s;
    cin >> s;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'X')
            numofx++;
        else {
            while (numofx >= 4) {
                ans.insert(ans.end(), 4, 'A');
                numofx -= 4;
            }
            while (numofx >= 2) {
                ans.insert(ans.end(), 2, 'B');
                numofx -= 2;
            }
            if (numofx == 1) {
                cout << -1;
                return 0;
            }
            ans.push_back('.');
        }
    }
    while (numofx >= 4) {
        ans.insert(ans.end(), 4, 'A');
        numofx -= 4;
    }
    while (numofx >= 2) {
        ans.insert(ans.end(), 2, 'B');
        numofx -= 2;
    }
    if (numofx == 1) {
        cout << -1;
        return 0;
    }
    for (vector<char>::const_iterator i = ans.begin(); i != ans.end();i++)
        cout << *i;
    return 0;
}
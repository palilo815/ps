#include<iostream>
#include<algorithm>
#include<string>
#include<unordered_map>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n, m;
    string s;
    cin >> n >> m;
    string* arr = new string[n];
    unordered_map<string, int> ump;

    for (int i = 0; i < n;i++) {
        cin >> s;
        arr[i] = s;
        ump[s] = i + 1;
    }
    while (m-- > 0) {
        cin >> s;
        if (s[0] < 'A') {
            int index = stoi(s);
            cout << arr[index - 1] << '\n';
        }
        else
            cout << ump.find(s)->second << '\n';
    }
    return 0;
}
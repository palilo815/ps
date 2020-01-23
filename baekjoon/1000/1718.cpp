#include<iostream>
#include<string>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    string s, key;
    getline(cin, s);
    cin >> key;
    int key_len = key.length();
    for (int i = 0; i < s.length();i++) {
        if (s[i] == ' ') cout << s[i];
        else {
            char c = s[i] - (key[i % key_len] - 96);
            if (c < 'a') c += 26;
            cout << c;
        }
    }
    return 0;
}
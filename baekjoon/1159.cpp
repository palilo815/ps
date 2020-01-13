#include<iostream>
using namespace std;

int main()
{
    int N, arr[26] = {};
    bool GG = true;
    string name;
    cin >> N;
    while (N-- > 0) {
        cin >> name;
        arr[name[0] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (arr[i] >= 5) {
            GG = false;
            cout << (char)(i + 'a');
        }
    }
    if (GG) cout << "PREDAJA";
    return 0;
}
#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int t, n;
    string s1, s2;
    cin >> t;
    while (t--) {
        cin >> s1 >> s2;
        cout << "Distances:";
        for (int i = 0; i < s1.size(); ++i) {
            n = s2[i] - s1[i];
            if (n < 0) n += 26;
            cout << " " << n;
        }
        cout << '\n';
    }
    return 0;
}
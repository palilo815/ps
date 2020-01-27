#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    unordered_map<int, int> mp;
    int n, x;
    cin >> n;
    while (n--) {
        cin >> x;
        if (mp.find(x) == mp.end()) mp[x] = 1;
        else ++(mp.find(x)->second);
    }
    cin >> n;
    while(n--) {
        cin >> x;
        auto it = mp.find(x);
        if (it == mp.end()) cout << 0 << ' ';
        else cout << it->second << ' ';
    }
    return 0;
}
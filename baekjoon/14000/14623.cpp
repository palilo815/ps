#include <bits/stdc++.h>
using namespace std;

int main() {
    bitset<32> a;
    bitset<32> b;
    cin >> a >> b;
    long long A = a.to_ullong(), B = b.to_ullong();
    bitset<64> C(A * B);
    string ans = C.to_string();
    int i = 0;
    while (ans[i] == '0') ++i;
    while (i < ans.size()) cout << ans[i++];
    return 0;
}
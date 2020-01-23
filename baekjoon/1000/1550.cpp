#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    string num;
    cin >> num;
    reverse(num.begin(), num.end());

    int ans = 0, n = 1;
    for (int i = 0; i < num.length(); i++) {
        int digit;
        if (num[i] < 'A') digit = num[i] - '0';
        else digit = num[i] - 'A' + 10;
        ans += digit * n;
        n *= 16;
    }
    cout << ans;
    return 0;
}
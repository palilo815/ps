#include <bits/stdc++.h>
using namespace std;

int main()
{
    string num; cin >> num;
    while (num.size() % 3) num.insert(num.begin(), '0');

    for (int i = 0; i < num.size(); i += 3) {
        int digit = 0;
        if (num[i] == '1') digit += 4;
        if (num[i + 1] == '1') digit += 2;
        if (num[i + 2] == '1') digit++;
        cout << digit;
    }
    return 0;
}
#include<iostream>
using namespace std;
int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n;
    cin >> n;
    int tmp = n;
    while (--tmp >= 0)
        cout << string(tmp, ' ') << string(n - tmp, '*') << '\n';
    return 0;
}
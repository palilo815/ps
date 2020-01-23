#include<iostream>
using namespace std;
int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n;
    cin >> n;
    while (n > 0)
        cout << n-- << '\n';
    return 0;
}
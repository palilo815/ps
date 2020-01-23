#include<iostream>
#include<algorithm>
using namespace std;

int* num;
void MakeOne(int n)
{
    if (n % 3 == 0) num[n] = 1 + min(num[n / 3], num[n - 1]);
    else if (n % 2 == 0) num[n] = 1 + min(num[n / 2], num[n - 1]);
    else num[n] = 1 + num[n - 1];
}
int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n;
    cin >> n;
    num = new int[n + 1];
    num[1] = 0;
    for (int i = 2; i <= n;i++)
        MakeOne(i);
    cout << num[n];
    return 0;
}
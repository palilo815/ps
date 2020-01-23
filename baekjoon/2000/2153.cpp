#include<iostream>
#include<algorithm>
using namespace std;
constexpr auto MAX = 1100;
bool IsPrime[MAX];

void Eratosthenes()
{
    for (int i = 2; i < MAX;i++)
        IsPrime[i] = true;
    IsPrime[0] = IsPrime[1] = false;
    for (int i = 2; i < MAX; i++) {
        if (IsPrime[i]) {
            for (int j = 2; j * i < MAX; j++)
                IsPrime[i * j] = false;
        }
    }
}

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    Eratosthenes();

    IsPrime[1] = true;
    string num;
    cin >> num;
    int sum = 0;
    for (int i = 0; i < num.length();i++) {
        if (num[i] < 'a')
            sum += num[i] - 38;
        else
            sum += num[i] - 96;
    }
    if (IsPrime[sum]) cout << "It is a prime word.";
    else cout << "It is not a prime word.";

    return 0;
}
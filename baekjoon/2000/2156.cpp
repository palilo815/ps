#include<iostream>
#include<algorithm>
using namespace std;

int len;
int* cache;
int* podo;

int Podoju(int n)
{
    if (n == len - 1) return podo[n];
    if (n > len - 1) return 0;

    if (cache[n] != -1) return cache[n];
    int ret;
    ret = max(podo[n] + Podoju(n + 2), podo[n] + podo[n + 1] + Podoju(n + 3));
    ret = max(ret, Podoju(n + 1));
    return cache[n] = ret;
}

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    cin >> len;
    cache = new int[len];
    podo = new int[len];
    for (int i = 0; i < len; i++)
        cache[i] = -1;
    for (int i = 0; i < len; i++)
        cin >> podo[i];

    cout << Podoju(0);
    return 0;
}
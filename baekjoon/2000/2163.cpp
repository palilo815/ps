#include<iostream>
#include<algorithm>
using namespace std;

int** cache;

int SPLIT(int x, int y)
{
    int G = max(x, y), L = min(x, y);
    int& ret = cache[G][L];
    if (ret != 0) return ret;
    if (L == 1) return ret = G - 1;

    if (G % 2 == 0) return ret = 1 + SPLIT(G / 2, L) * 2;
    else return ret = 1 + SPLIT(G / 2, L) + SPLIT(G / 2 + 1, L);
}

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int x, y;
    cin >> x >> y;
    int G = max(x, y), L = min(x, y);
    cache = new int* [G + 1];
    for (int i = 0; i < G + 1; i++)
        cache[i] = new int[L + 1]{};
    cout << SPLIT(G, L);
    return 0;
}
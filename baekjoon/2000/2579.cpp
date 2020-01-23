#include<iostream>
#include<algorithm>
using namespace std;

int len;
int* cache;
int* score;

int Sum(int n)
{
    int& ret = cache[n];
    if (ret != 0) return ret;
    if (n == len - 1) return ret = score[len - 1];
    if (n == len - 2) return ret = score[len - 2] + score[len - 1];
    if (n == len - 3) return ret = score[len - 3] + score[len - 1];
    return ret = max(score[n] + Sum(n + 2), score[n] + score[n + 1] + Sum(n + 3));
}

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    cin >> len;
    cache = new int[len] {};
    score = new int[len];

    for (int i = 0; i < len; i++)
        cin >> score[i];
    if (len == 1)
        cout << score[0];
    else
        cout << max(Sum(0), Sum(1));
    return 0;
}
#include<iostream>
#include<algorithm>
using namespace std;
int n;
int** cost;
int** cache;

int MinCost(int x, int color)
{
    if (x == n) return 0;

    int& ret = cache[x][color];
    if (ret != 0) return ret;
    if (color == 0)
        return ret = min(cost[x][1] + MinCost(x + 1, 1), cost[x][2] + MinCost(x + 1, 2));
    else if (color == 1)
        return ret = min(cost[x][0] + MinCost(x + 1, 0), cost[x][2] + MinCost(x + 1, 2));
    else
        return ret = min(cost[x][0] + MinCost(x + 1, 0), cost[x][1] + MinCost(x + 1, 1));
}

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    cin >> n;
    cost = new int* [n];
    cache = new int* [n];

    for (int i = 0; i < n; i++)
        cost[i] = new int[3];
    for (int i = 0; i < n; i++)
        cache[i] = new int[3]{};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 3; j++)
            cin >> cost[i][j];

    int ans = min(cost[0][0] + MinCost(1, 0), cost[0][1] + MinCost(1, 1));
    ans = min(ans, cost[0][2] + MinCost(1, 2));
    cout << ans;
    return 0;
}
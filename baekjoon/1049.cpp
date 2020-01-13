#include<iostream>
#include<algorithm>
using namespace std;

struct brand {
    int cost_6;
    int cost_1;
};

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int str, n, min_6, min_1;
    cin >> str >> n;
    brand* arr = new brand[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i].cost_6 >> arr[i].cost_1;

    min_6 = min(arr[0].cost_6, arr[0].cost_1 * 6);
    min_1 = arr[0].cost_1;

    for (int i = 1;i < n;i++) {
        if (arr[i].cost_1 < min_1) min_1 = arr[i].cost_1;
        int tmp = min(arr[i].cost_6, arr[i].cost_1 * 6);
        if (tmp < min_6) min_6 = tmp;
    }

    int cost = 0;
    while (str >= 6) cost += min_6, str -= 6;
    cost += min(str * min_1, min_6);
    cout << cost;
    return 0;
}
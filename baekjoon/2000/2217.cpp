#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n;
    cin >> n;
    int* weight = new int[n];
    for (int i = 0; i < n; i++)
        cin >> weight[i];
    sort(weight, weight + n);
    int count = 1, max = 0;
    for (int i = n - 1; i >= 0; i--) {
        int tmp = weight[i] * count;
        if (tmp > max)
            max = tmp;
        count++;
    }
    cout << max;
    return 0;
}
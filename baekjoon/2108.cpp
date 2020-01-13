#include<iostream>
#include<math.h>
#include<algorithm>
#include<queue>
using namespace std;

int arr[8001] = {};
int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n, x, sum = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        sum += x;
        arr[x + 4000]++;
    }
    cout << round((double)sum / n) << '\n';

    int left = 0, right = n - 1, count = 0;
    for (int i = 0; i < 8001; i++)
        if (arr[i] != 0) {
            left = i;
            break;
        }
    for (int i = 8000; i >= 0; i--)
        if (arr[i] != 0) {
            right = i;
            break;
        }

    int max_repeated = 0, MidVal = 0;
    bool IsItSecond = false, FindMidVal = false;

    for (int i = left; i <= right; i++) {
        count += arr[i];
        if (arr[i] > arr[max_repeated]) {
            max_repeated = i;
            IsItSecond = false;
        }
        else if (arr[i] == arr[max_repeated]) {
            if (!IsItSecond) {
                max_repeated = i;
                IsItSecond = true;
            }
        }
        if (count >= (n + 1) / 2 && !FindMidVal) {
            FindMidVal = true;
            MidVal = i;
        }
    }
    cout << MidVal - 4000 << '\n' << max_repeated - 4000 << '\n' << right - left;
    return 0;
}
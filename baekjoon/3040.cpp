#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool flag[9];
int main()
{
    int arr[9], sum = 0;
    loop(i, 9) {
        cin >> arr[i];
        sum += arr[i];
    }

    int gap = sum - 100;
    loop(i, 8)
        for (int j = i + 1; j < 9; j++)
            if (arr[i] + arr[j] == gap)
                flag[i] = true, flag[j] = true;
    loop(i, 9) if (!flag[i])
        cout << arr[i] << '\n';
    return 0;
}

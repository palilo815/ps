#include<iostream>
using namespace std;
int main()
{
    int room;
    cin >> room;
    if (room == 0) {
        cout << "1";
        return 0;
    }
    int arr[10] = {};
    while (room > 0) {
        arr[room % 10]++;
        room /= 10;
    }
    arr[6] += arr[9];
    if (arr[6] % 2 == 0)
        arr[6] /= 2;
    else
        arr[6] = (arr[6] + 1) / 2;
    int max = arr[0];
    for (int i = 1; i < 9; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    cout << max;
    return 0;
}
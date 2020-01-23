#include <stdio.h>
#include <stdlib.h>
#define swap(x, y) do{ int t = x; x = y; y = t;}while(0)
void sorting(int arr[])
{
    for (int i = 1; i < 9; i++) {
        int index = i;
        while (index > 0 && arr[index - 1] > arr[index]) {
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
}
int main()
{
    int arr[9], sum = 0;
    for (int i = 0; i < 9; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    sorting(arr);
    int gap = sum - 100;
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (arr[i] + arr[j] == gap) {
                for (int k = 0; k < 9; k++) {
                    if (k == i || k == j)
                        continue;
                    else
                        printf("%d\n", arr[k]);
                }
                return 0;
            }
        }
    }
    return 0;
}
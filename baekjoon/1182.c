#include <stdio.h>
#include <stdlib.h>
#define swap(x, y) do{ int t = x; x = y; y = t;}while(0)

void InsertionSorting(int arr[], int size)
{
    for (int i = 1; i < size; i++) {
        int index = i;
        while (index > 0 && arr[index - 1] > arr[index]) {
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
}
void BFsearch(int arr[], int index, int size, int sum, int val, int* count)
{
    if (index >= size)
        return;
    BFsearch(arr, index + 1, size, sum, val, count);
    sum += arr[index];
    if (sum == val)
        (*count)++;
    BFsearch(arr, index + 1, size, sum, val, count);
}
int main()
{
    int N, val;
    scanf("%d %d", &N, &val);
    int* arr = (int*)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);
    InsertionSorting(arr, N);
    int count = 0;
    BFsearch(arr, 0, N, 0, val, &count);
    printf("%d", count);
    return 0;
}
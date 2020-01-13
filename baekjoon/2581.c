#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void MakePrimeArr(int arr[])
{
    int count = 1;
    bool ItIsPrime;
    for (int i = 3; i <= 10000; i++) {
        ItIsPrime = true;
        for (int j = 0; j < count; j++) {
            if (i % arr[j] == 0)
                ItIsPrime = false;
        }
        if (ItIsPrime)
            arr[count++] = i;
    }
}
int main()
{
    int prime[1229] = { 2, };
    int A, B;
    scanf("%d %d", &A, &B);
    MakePrimeArr(prime);
    int min = 0;
    while (prime[min] < A)
        min++;
    int sum = 0;
    for (int i = min; prime[i] <= B; i++)
        sum += prime[i];
    if (sum)
        printf("%d\n%d", sum, prime[min]);
    else
        printf("-1");
    return 0;
}
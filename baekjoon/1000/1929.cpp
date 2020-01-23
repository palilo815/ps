#include<iostream>
using namespace std;
bool PrimeCheck(int* prime, int val)
{
    for (int i = 0; prime[i] * prime[i] <= val; i++)
        if (val % prime[i] == 0)
            return false;
    return true;
}

int main()
{
    int A, B, i;
    cin >> A >> B;
    int count = 1;
    int prime[80000] = { 2, };
    for (i = 3; i <= B;i += 2) {
        if (PrimeCheck(prime, i)) {
            prime[count++] = i;
        }
    }
    for (i = 0; prime[i] < A;i++) {}
    for (i; i < count; i++)
        printf("%d\n", prime[i]);

    return 0;
}
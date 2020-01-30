#include <stdio.h>

int main()
{
    int k;
    scanf("%d", &k);
    int n = k;
    while (n > 2) {
        printf("%d bottles of beer on the wall, %d bottles of beer.\nTake one down and pass it around, %d bottles of beer on the wall.\n\n", n, n, n - 1);
        --n;
    }
    while (n > 1) {
        printf("%d bottles of beer on the wall, %d bottles of beer.\nTake one down and pass it around, %d bottle of beer on the wall.\n\n", n, n, n - 1);
        --n;
    }
    printf("1 bottle of beer on the wall, 1 bottle of beer.\nTake one down and pass it around, no more bottles of beer on the wall.\n\nNo more bottles of beer on the wall, no more bottles of beer.\nGo to the store and buy some more, %d ", k);
    if (k == 1) printf("bottle");
    else printf("bottles");
    printf(" of beer on the wall.");
    return 0;
}
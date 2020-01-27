#include <stdio.h>

int main()
{
    double hotdog, people;
    while (scanf("%lf %lf", &hotdog, &people) != -1)
        printf("%.2f\n", hotdog / people);
    return 0;
}
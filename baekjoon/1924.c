#include<stdio.h>

int DAY(int m);
int main()
{
    int x, y;
    scanf("%d %d", &x, &y);

    x--;
    while (x >= 1)
    {
        y += DAY(x);
        x--;
    }
    switch (y % 7)
    {
    case 1: printf("MON");
        break;
    case 2: printf("TUE");
        break;
    case 3: printf("WED");
        break;
    case 4: printf("THU");
        break;
    case 5: printf("FRI");
        break;
    case 6: printf("SAT");
        break;
    case 0: printf("SUN");
        break;
    }
    return 0;
}

int DAY(int m)
{
    int day;
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        day = 31;
    else if (m == 2)
        day = 28;
    else
        day = 30;

    return day;
}
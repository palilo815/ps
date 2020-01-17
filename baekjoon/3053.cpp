#include<iostream>
#define PI 3.14159265358979323846
using namespace std;

int main()
{
    int r; cin >> r;
    double circle_U = PI * r * r;
    double circle_T = 2 * r * r;
    printf("%6lf\n%6lf", circle_U, circle_T);
    return 0;
}
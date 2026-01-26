#include <limits.h>
#include <math.h>
#include <stdio.h>

int main()
{
    float x = 0.2, Eps = 0.0001, z = 0;
    int n = 1;

    while (n < INT_MAX && fabs((1.0 / (2 * n + 1)) * pow((x - 1) / (x + 1), 2 * n + 1)) > Eps)
    {
        z += (1.0 / (2 * n + 1)) * pow((x - 1) / (x + 1), 2 * n + 1);
        n++;
    }

    printf("result = %f",z);
    return  0;
}

#include <limits.h>
#include <math.h>
#include <stdio.h>
int main()
{
    float z;
    for (float n = 1, Eps = 0.0001, x = 0.2; fabs((1.0 / (2 * n + 1)) * pow((x - 1) / (x + 1), 2 * n + 1)) > Eps && n < INT_MAX;z += (1.0 / (2 * n + 1)) * pow((x - 1) / (x + 1), 2 * n + 1), n++)
    {

    }

    printf("result = %f", z);
    return 0;
}   

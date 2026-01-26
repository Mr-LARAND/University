#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define n 9


void matrix_fill(float a[][n])
{
    int i,j;
    for (i=0;i<n;i++)
    {
            for (j=0;j<n;j++)
            {
               a[i][j]=(float) rand()/rand();
                printf("%f\t",a[i][j]);
            }
             printf("\n");

    }
     printf("\n");

}

int main()
{
    int i,j;
    float m = 0, max = 0;
    float matrix[n][n];
    matrix_fill(matrix);
    for (i=0;i<n;i++)
    {
            for (j=0;j<n;j++)
            {
                    if (i<j && i<(n-1)/2) matrix[i][j]=0;

                    if (i>j &&  i>(n-1)/2) matrix[i][j]=0;

                    if (matrix[i][j] > max) max = matrix[i][j];

                    printf("%f\t",matrix[i][j]);

            }
            printf("\n");
    }
    printf("\nMaximum value = %f", max);
    return 0;
}

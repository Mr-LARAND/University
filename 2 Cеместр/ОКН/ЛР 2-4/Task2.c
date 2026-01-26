#include <stdio.h>
#include <math.h>

void factorial_m(int n, double matrix[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) 
        {
            matrix[i][j] = 1.0 / pow(j + 1, i + 1);
        }
    }
}

void print_m(int n, double matrix[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) 
        {
            printf("%f", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the order of the matrix n: ");
    scanf("%d", &n);

    double matrix[n][n];
    factorial_m(n, matrix);
    print_m(n, matrix);

    int z=3, x=4;

    z=(x>0)+ ++x;

    return 0;
}

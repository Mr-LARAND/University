#include <stdio.h>
#include <stdlib.h>

#define N 8

int array_x[N];
int count = 0;

int place_is_free(int k)
{
    for (int i = 0; i < k; i++)
    {
        if (array_x[i] == array_x[k] || abs(array_x[i] - array_x[k]) == abs(i - k))
            return 0;
    }
    return 1;
}

void print_board()
{
    printf("Решение %d:\n", ++count);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (array_x[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

void queen(int k)
{
    for (array_x[k] = 0; array_x[k] < N; array_x[k]++)
    {
        if (place_is_free(k))
        {
            if (k == N - 1)
                print_board();
            else
                queen(k + 1);
        }
    }
}

int main()
{
    queen(0);
    printf("Всего решений: %d\n", count);
    return 0;
}
/*
Задача о восьми ферзях.
На шахматную доску необходимо поставить 8 ферзей, чтобы они не били
друг друга. Шахматная доска имеет размер 8 x 8. Ферзь ходит по диаго-
нали, вертикали и горизонтали.
Необходимо написать программу для решения задачи в следующих
вариациях:
1. Найти одну расстановку ферзей на шахматной доске.
*/

#include <stdio.h>
#include <stdlib.h>

#define N 8

int array_x[N]; // столбец ферзя в строке i
                // индекс массива = номер строки
                // значение = номер столбца
int found = 0;

int place_is_free(int k) // к-я строка
{
    for (int i = 0; i < k; i++)
        if (array_x[i] == array_x[k] || abs(array_x[i] - array_x[k]) == abs(i - k))
            return 0;
    return 1;
}

void queen(int k)
{
    for (array_x[k] = 0; array_x[k] < N; array_x[k]++)
    {
        if (place_is_free(k))
        {
            if (k == N - 1) {
                found = 1;
                return;
            }
            else
                queen(k + 1);
        }
        if (found) 
            return;
    }
}

void print_board()
{
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
}

int main()
{
    queen(0);
    if (found)
        print_board();
    else
        printf("Решение не найдено\n");

    return 0;
}
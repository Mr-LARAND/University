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

#define DIMENSION 8

int board[DIMENSION]; // столбец ферзя в строке i
                // индекс массива = номер строки
                // значение = номер столбца
int found = 0;

int place_is_free(int j) // j-я строка
{
    for (int i = 0; i < j; i++)
        if (board[i] == board[j] || abs(board[i] - board[j]) == abs(i - j))
            return 0;
    return 1;
}

void solve(int j)
{
    for (board[j] = 0; board[j] < DIMENSION; board[j]++)
    {
        if (place_is_free(j))
        {
            if (j == DIMENSION - 1) {
                found = 1;
                return;
            }
            else
                solve(j + 1);
        }
        if (found) 
            return;
    }
}

void print_result()
{
    for (int i = 0; i < DIMENSION; i++)
        for (int j = 0; j < DIMENSION; j++)
            if (board[i] == j)
                printf("%d", board[i]);
    printf("\n");
}

int main()
{
    solve(0);
    if (found)
        print_result();

    return 0;
}
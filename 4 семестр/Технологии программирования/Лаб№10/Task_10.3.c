/*
Задача о восьми ферзях.
На шахматную доску необходимо поставить 8 ферзей, чтобы они не били
друг друга. Шахматная доска имеет размер 8 x 8. Ферзь ходит по диаго-
нали, вертикали и горизонтали.
Необходимо написать программу для решения задачи в следующих
вариациях:
3. Найти уникальные расстановки ферзей.

-> - ПОВОРОТ   * - ОТРАЖЕНИЕ ПО ПРОЯМОЙ   % - ОТРАЖЕНИЕ ДИАГОНАЛЬ
// 25317460 -> ⁡⁢⁢⁢04752613⁡ -> 71306425 -> 46152037 * 52460317 * 06471352 % 73025164 % 31625740

// не прышать на ваосьмёрке смотреть конкретно число

мы нашли решение -> передали его проверяться на эквивалентность, то есть мы его покрутиили 4 раза, отразили 4 раза, 
нашли минимальное это и есть наше уникальное решение*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIMENSION 13

int board[DIMENSION]; // столбец ферзя в строке i
                // индекс массива = номер строки
                // значение = номер столбца
int unique_count = 0;

// Ф-я проверки доступности места
int place_is_free(int j) 
{
    for (int i = 0; i < j; i++)
        if (board[i] == board[j] || abs(board[i] - board[j]) == abs(i - j))
            return 0;
    return 1;
}

void copy_solution(int dest[], int src[]) {
    for (int i = 0; i < DIMENSION; i++)
        dest[i] = src[i];
}

void rotate(int src[], int dest[]) {
    for (int i = 0; i < DIMENSION; i++)
        dest[src[i]] = DIMENSION - 1 - i;
}

void reflect(int src[], int dest[]) {
    for (int i = 0; i < DIMENSION; i++)
        dest[i] = DIMENSION - 1 - src[i];
}

int build_digit(int *array, size_t size_arr)
{
    int digit = 0;
    for (int i = 0; i < size_arr; i++) 
        digit = digit * 10 + array[i];
    return digit;
}

// Ф-я сборки уникального решения
int is_unique(int *solution) 
{
    int original = build_digit(solution, DIMENSION);

    int temp[DIMENSION];
    int work[DIMENSION];

    copy_solution(temp, solution);

    for (int i = 0; i < 3; i++) 
    {
        rotate(temp, work);
        int d = build_digit(work, DIMENSION);

        if (original > d)
            return 0;

        copy_solution(temp, work);
    }

    reflect(solution, temp);
    int d = build_digit(temp, DIMENSION);
    if (original > d)
        return 0;

    for (int i = 0; i < 3; i++) 
    {
        rotate(temp, work);
        d = build_digit(work, DIMENSION);

        if (original > d)
            return 0;

        copy_solution(temp, work);
    }

    unique_count++;
    return 1;
}

// Ф-я поиска решения (алгоритм BackTraking)
void solve(int j) 
{
    if (j == DIMENSION) {
        is_unique(board);
        return;
    }

    for (board[j] = 0; board[j] < DIMENSION; board[j]++)
        if (place_is_free(j)) {
            board[j] = board[j];
            solve(j + 1);
        }
}

int main() 
{
    solve(0);
    printf("%d\n", unique_count);
    return 0;
}
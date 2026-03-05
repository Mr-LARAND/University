/*
Задача о восьми ферзях.
На шахматную доску необходимо поставить 8 ферзей, чтобы они не били
друг друга. Шахматная доска имеет размер 8 x 8. Ферзь ходит по диаго-
нали, вертикали и горизонтали.
Необходимо написать программу для решения задачи в следующих
вариациях:
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int unique_count = 0;

//  Ф-я проверки доступности места
int place_is_free(int j, int board[]) 
{
    for (int i = 0; i < j; i++)
        if (board[i] == board[j] || abs(board[i] - board[j]) == abs(i - j))
            return 0;
    return 1;
}

void copy_solution(int dest[], int src[], int size) {
    for (int i = 0; i < size; i++)
        dest[i] = src[i];
}

void rotate(int src[], int dest[], int size) {
    for (int i = 0; i < size; i++)
        dest[src[i]] = size - 1 - i;
}

void reflect(int src[], int dest[], int size) {
    for (int i = 0; i < size; i++)
        dest[i] = size - 1 - src[i];
}

int build_digit(int *array, size_t size_arr)
{
    int digit = 0;
    for (int i = 0; i < size_arr; i++) 
        digit = digit * 10 + array[i];
    return digit;
}

// Ф-я сборки уникального решения
int is_unique(int *solution, int size) 
{
    int original = build_digit(solution, size);

    int temp[size];
    int work[size];

    copy_solution(temp, solution, size);

    for (int i = 0; i < 3; i++) 
    {
        rotate(temp, work, size);
        int d = build_digit(work, size);

        if (original > d)
            return 0;

        copy_solution(temp, work, size);
    }

    reflect(solution, temp, size);
    int d = build_digit(temp, size);
    if (original > d)
        return 0;

    for (int i = 0; i < 3; i++) 
    {
        rotate(temp, work, size);
        d = build_digit(work, size);

        if (original > d)
            return 0;

        copy_solution(temp, work, size);
    }

    unique_count++;
    return 1;
}

// Ф-я поиска решения (алгоритм BackTraking)
void solve(int j, int *board, int size) 
{
    if (j == size) {
        is_unique(board, size);
        return;
    }

    for (board[j] = 0; board[j] < size; board[j]++)
        if (place_is_free(j, board)) {
            board[j] = board[j];
            solve(j + 1, board, size);
        }
}

int main() 
{
    int size;
    printf("Please Enter the dimension board:\n");
    if (scanf("%d", &size) != 1) {
        printf("Error input...\n");  
        return 1;
    }

    int board_1[size];
    solve(0, board_1, size);
    printf("%d\n", unique_count);
    return 0;
}
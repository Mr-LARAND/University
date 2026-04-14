/* 
Создать статическую и динамическую библиотеку, содержащую
следующие функции: вычисления обратной матрицы методом Гаус-
са, методом Жордана-Гаусса. Написать программу, тестирующую
функции из библиотеки. Создать файл сборки для компиляции биб-
лиотечных файлов, сборки и запуска исполняемого файла, удаления
объектных файлов. Вместо отчёта по лабораторной предусмотреть
описание сборки и использования библиотеки в формате markdown.
*/
#include <stdio.h>
#include "matrix.h"

// Вспомогательная функция для красивого вывода матрицы на экран
void print_matrix(double** matrix, int n) 
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%8.4f ", matrix[i][j]); 
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int n = 3;

    double** matrix = allocate_matrix(n, n);
    double** matrix_inv_jordan = allocate_matrix(n, n);
    double** matrix_inv_gauss = allocate_matrix(n, n);

    if (!matrix || !matrix_inv_jordan || !matrix_inv_gauss) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    double temp_data[3][3] = {
        {4.0, 2.0, 9.0},
        {6.0, 3.0, 0.0},
        {2.0, 4.0, 7.0}
    };

    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            matrix[i][j] = temp_data[i][j];

    printf("Исходная матрица:\n");
    print_matrix(matrix, n);

    // Метод Жордана-Гаусса
    printf("Метод Жордана-Гаусса:\n");
    if (gauss_jordan_inverse(matrix, matrix_inv_jordan, n))
        print_matrix(matrix_inv_jordan, n); 
    else 
        printf("Обратная матрица не найдена.\n\n");

    // Классический метод Гаусса
    printf("Классический метод Гаусса:\n");
    if (gauss_inverse(matrix, matrix_inv_gauss, n))
        print_matrix(matrix_inv_gauss, n); 
    else
        printf("Обратная матрица не найдена.\n\n");

    free_matrix(matrix, n);
    free_matrix(matrix_inv_jordan, n);
    free_matrix(matrix_inv_gauss, n);

    return 0;
}

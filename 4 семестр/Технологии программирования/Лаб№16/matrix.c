#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "matrix.h"

#define EPS 1e-9

// Ф-я выделения памяти под матрицу
double** allocate_matrix(int rows, int cols) 
{
    double** matrix = (double**)malloc(rows * sizeof(double*));
    if (!matrix) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
        if (!matrix[i]) {
            printf("Ошибка выделения памяти\n");
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

// Ф-я освобождения памяти
void free_matrix(double** matrix, int rows) 
{
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}

// Метод Жордана-Гаусса для нахождения обратной матрицы
// Входная матрица A трансформируется в обратную
bool gauss_jordan_inverse(double** A, double** A_inv, int n) 
{
    // Создаем расширенную матрицу [A | E]
    double** augmented = allocate_matrix(n, 2 * n);
    
    // Копируем A в левую часть и создаем единичную матрицу справа
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = A[i][j];
            augmented[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }
    
    // Прямой ход: приведение к верхнетреугольной матрице
    for (int i = 0; i < n; i++) 
    {
        // Поиск опорного элемента
        int pivot_row = i;
        for (int k = i + 1; k < n; k++)
            if (fabs(augmented[k][i]) > fabs(augmented[pivot_row][i]))
                pivot_row = k;
        
        // Проверка на вырожденность матрицы
        if (fabs(augmented[pivot_row][i]) < EPS) {
            printf("Матрица вырождена (не имеет обратной)!\n");
            free_matrix(augmented, n);
            return false;
        }
        
        // Перестановка строк
        if (pivot_row != i) {
            double* temp = augmented[i];
            augmented[i] = augmented[pivot_row];
            augmented[pivot_row] = temp;
        }
        
        // Нормализация строки: делим на диагональный элемент
        double pivot = augmented[i][i];
        for (int j = 0; j < 2 * n; j++)
            augmented[i][j] /= pivot;
        
        // Исключение элементов в столбце (обратный ход Жордана)
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = augmented[k][i];
                for (int j = 0; j < 2 * n; j++)
                    augmented[k][j] -= factor * augmented[i][j];
            }
        }
    }
    
    // Копируем обратную матрицу из правой части расширенной матрицы
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A_inv[i][j] = augmented[i][j + n];
    
    free_matrix(augmented, n);
    return true;
}

// Классический метод Гаусса для нахождения обратной матрицы
bool gauss_inverse(double** A, double** A_inv, int n) 
{
    // Создаем расширенную матрицу [A | E]
    double** augmented = allocate_matrix(n, 2 * n);
    if (!augmented) return false;

    // Копируем A в левую часть и создаем единичную матрицу справа
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = A[i][j];
            augmented[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }

    // 1. ПРЯМОЙ ХОД (приведение к верхнетреугольному виду)
    for (int i = 0; i < n; i++) {
        // Поиск опорного элемента (pivoting)
        int pivot_row = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(augmented[k][i]) > fabs(augmented[pivot_row][i])) {
                pivot_row = k;
            }
        }

        // Проверка на вырожденность
        if (fabs(augmented[pivot_row][i]) < EPS) {
            printf("Матрица вырождена (не имеет обратной)!\n");
            free_matrix(augmented, n);
            return false;
        }

        // Перестановка строк, если нужно
        if (pivot_row != i) {
            double* temp = augmented[i];
            augmented[i] = augmented[pivot_row];
            augmented[pivot_row] = temp;
        }

        // В отличие от Жордана-Гаусса, мы обнуляем элементы ТОЛЬКО СНИЗУ от главной диагонали
        for (int k = i + 1; k < n; k++) {
            double factor = augmented[k][i] / augmented[i][i];
            // Вычитаем i-ю строку, умноженную на коэффициент, из k-й строки
            for (int j = i; j < 2 * n; j++) {
                augmented[k][j] -= factor * augmented[i][j];
            }
        }
    }

    // 2. ОБРАТНЫЙ ХОД (обратная подстановка)
    // Решаем СЛАУ для каждого столбца правой части расширенной матрицы
    for (int col = 0; col < n; col++) {
        for (int i = n - 1; i >= 0; i--) {
            double sum = 0.0;
            // Вычисляем сумму известных членов (правее диагонали)
            for (int j = i + 1; j < n; j++) {
                sum += augmented[i][j] * A_inv[j][col];
            }
            // Находим неизвестный элемент: (правая часть - сумма) / диагональный элемент
            A_inv[i][col] = (augmented[i][n + col] - sum) / augmented[i][i];
        }
    }

    free_matrix(augmented, n);
    return true;
}

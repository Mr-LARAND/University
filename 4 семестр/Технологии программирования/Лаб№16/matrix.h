#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

/*
 * Выделение памяти под матрицу
 * rows - количество строк
 * cols - количество столбцов
 * return: matrix при успехе, NULL при ошибке.
*/
double** allocate_matrix(int rows, int cols);

/*
 * Освобождение памяти, выделенной под матрицу
 * matrix - указатель на матрицу
 * rows - количнство строк
*/
void free_matrix(double** matrix, int rows);

/*
 * Метод Жордана Гаусса
 * A - исходная матрица
 * A_inv - обратная матрица(после преобразования исходной)
 * n - размерность матрицы
 * return: false - обратной матрицы не существет, true - обрфтная матрица найдена.
*/
bool gauss_jordan_inverse(double** A, double** A_inv, int n);

/*
 * Метод Гаусса (классический)
 * A - исходная матрица
 * A_inv - обратная матрица
 * n - размерность матрицы
 * return: false - обратной матрицы не существует, true - обратная матрица найдена.
 */
bool gauss_inverse(double** A, double** A_inv, int n);


#endif
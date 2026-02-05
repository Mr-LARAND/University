/*
В результате эксперимента была определена некоторая табличная зави-
симость. С помощью метода наименьших квадратов⁡⁡ определить ⁡⁢⁢⁣линию
регрессии⁡,⁡⁣⁣⁢|⁡ ⁡⁢⁢⁣рассчитать коэффициент корреляции⁡⁡,⁡⁣⁣⁢|⁡ ⁡⁢⁢⁣подобрать функцио-
нальную зависимость заданного вида⁡,⁡⁣⁣⁢|⁡ ⁡⁢⁢⁣вычислить индекс корреляции⁡.
Построить график экспериментальной зависимости, линию регрессии и
график подобранной зависимости. ⁡⁢⁢⁣Определить суммарную квадратичную
ошибку⁡, ⁡⁢⁢⁣среднюю и относительные ошибки для линии регрессии и подо-
бранной функциональной зависимости⁡. Написать программу для решения
задачи. Исходные данные для программы хранятся в файле. Структу-
ру файла разработать самостоятельно. Решение проверить с помощью
известного Вам математического пакета.
Q(s) = As^2 + Bs + C

s   1   1.25  1.5  1.75   2    2.25   2.5   2.75   3
Q 5.21 4.196 3.759 3.672 4.592 4.621 5.758 7.173 9.269

SSE - сумма квадратов ошибок (Sum of Squared Errors) = ∑(Qi−Q^i)2∑(Qi−Q^i)2
MSE - средняя квадратичная ошибка (Mean Squared Error) = SSE / N
RMSE - корень из MSE (Root Mean Squared Error) = MSE*MSE
MAE (Mean Absolute Error) = средняя абсолютная ошибка
MARE (Mean Absolute Relative Error) = средняя относительная ошибка в %
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 9  // количество точек

// Ф-я для решения системы 3x3 методом Гаусса
void solve_3x3(double A[3][3], double b[3], double x[3]) 
{
    double aug[3][4];
    
    // Создаём расширенную матрицу [A|b]
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            aug[i][j] = A[i][j];
        aug[i][3] = b[i];
    }
    
    // Прямой ход
    for (int k = 0; k < 3; k++)
        for (int i = k + 1; i < 3; i++) {
            double factor = aug[i][k] / aug[k][k];
            for (int j = k; j < 4; j++)
                aug[i][j] -= factor * aug[k][j];
        }
    
    // Обратный ход
    for (int i = 2; i >= 0; i--) {
        x[i] = aug[i][3];
        for (int j = i + 1; j < 3; j++)
            x[i] -= aug[i][j] * x[j];
        x[i] /= aug[i][i];
    }
}

// Функция для решения системы 2x2
void solve_2x2(double A[2][2], double b[2], double x[2]) 
{
    double determinant = A[0][0] * A[1][1] - A[0][1] * A[1][0];
    x[0] = (b[0] * A[1][1] - b[1] * A[0][1]) / determinant;
    x[1] = (A[0][0] * b[1] - A[1][0] * b[0]) / determinant;
}

int main() 
{
    // Исходные данные
    double s[N] = {1, 1.25, 1.5, 1.75, 2, 2.25, 2.5, 2.75, 3};
    double Q[N] = {5.21, 4.196, 3.759, 3.672, 4.592, 4.621, 5.758, 7.173, 9.269};
    
    // ⁣ЛИНЕЙНАЯ РЕГРЕССИЯ⁡⁡ Q = a + b*s
    double sum_s = 0, sum_Q = 0, sum_s_2 = 0, sum_sQ = 0, sum_Q_2 = 0;
    
    for (int i = 0; i < N; i++) 
    {
        sum_s += s[i];
        sum_Q += Q[i];
        sum_s_2 += s[i] * s[i];
        sum_sQ += s[i] * Q[i];
        sum_Q_2 += Q[i] * Q[i]; // Нужно для коэффициента кореляции
    }
    
    double mean_s = sum_s / N;
    double mean_Q = sum_Q / N;
    
    // Решаем систему для линейной регрессии в матр. виде Ax = b
    // Матрица A
    double A_lin[2][2] = {
        {sum_s_2, sum_s},
        {sum_s, N}
    };

    double b_lin[2] = {sum_sQ, sum_Q}; // вектор справа 
    double coef_lin[2];  // вектор [b, a]
    
    solve_2x2(A_lin, b_lin, coef_lin);
    double b_coef = coef_lin[0];
    double a_coef = coef_lin[1];
    
    printf("\nЛинейная регрессия: Q(s) = %.4f + %.4fs\n", a_coef, b_coef);
    
    // Коэффициент корреляции
    double numerator = N * sum_sQ - sum_s * sum_Q;
    double denominator = sqrt((N * sum_s_2 - sum_s * sum_s) * (N * sum_Q_2 - sum_Q * sum_Q));
    double r = numerator / denominator;
    
    printf("Коэффициент корреляции r = %.4f\n\n", r);
    
    // Ошибки для линейной регрессии
    double SSE_lin = 0, sum_abs_err_lin = 0, sum_rel_err_lin = 0;
    
    printf("Точка | s     | Q_изм  | Q_лин  | Ошибка  | Отн.ошибка\n");
    printf("------|-------|--------|--------|---------|------------\n");
    
    for (int i = 0; i < N; i++) 
    {
        double Q_pred = a_coef + b_coef * s[i];
        double error = Q[i] - Q_pred;
        double rel_error = fabs(error / Q[i]) * 100;
        
        SSE_lin += error * error;
        sum_abs_err_lin += fabs(error);
        sum_rel_err_lin += rel_error;
        
        printf("  %d   | %.2f  | %.3f  | %.3f  | %7.3f | %6.2f%%\n",
               i+1, s[i], Q[i], Q_pred, error, rel_error);
    }
    
    double MSE_lin = SSE_lin / N;
    double RMSE_lin = sqrt(MSE_lin);
    double MAE_lin = sum_abs_err_lin / N;
    double MARE_lin = sum_rel_err_lin / N;
    
    printf("\nСуммарная квадратичная ошибка: %.6f\n", SSE_lin);
    printf("Средняя квадратичная ошибка:    %.6f\n", MSE_lin);
    printf("Средняя абсолютная ошибка:      %.6f\n", MAE_lin);
    printf("Средняя относительная ошибка:         %.2f%%\n\n", MARE_lin);
    
    // ============= ЧАСТЬ 2: КВАДРАТИЧНАЯ ЗАВИСИМОСТЬ Q = A*s² + B*s + C =============
    
    double sum_s3 = 0, sum_s4 = 0, sum_s2Q = 0;
    
    for (int i = 0; i < N; i++) 
    {
        double s2 = s[i] * s[i];
        double s3 = s2 * s[i];
        double s4 = s3 * s[i];
        
        sum_s3 += s3;
        sum_s4 += s4;
        sum_s2Q += s2 * Q[i];
    }
    
    // Система нормальных уравнений для квадратичной регрессии
    double A_quad[3][3] = {
        {sum_s4, sum_s3, sum_s_2},
        {sum_s3, sum_s_2, sum_s},
        {sum_s_2, sum_s, N}
    };
    double b_quad[3] = {sum_s2Q, sum_sQ, sum_Q};
    double coef_quad[3];  // [A, B, C]
    
    solve_3x3(A_quad, b_quad, coef_quad);
    double A_par = coef_quad[0];
    double B_par = coef_quad[1];
    double C_par = coef_quad[2];
    
    printf("Квадратичная зависимость: Q(s) = %.4f * s² + %.4f * s + %.4f\n\n", A_par, B_par, C_par);
    
    // Индекс корреляции (coefficient of determination R²)
    double SST = 0;  // Total sum of squares
    for (int i = 0; i < N; i++)
        SST += (Q[i] - mean_Q) * (Q[i] - mean_Q);
    
    double SSE_quad = 0, sum_abs_err_quad = 0, sum_rel_err_quad = 0;
    
    printf("Точка | s     | Q_изм  | Q_квад | Ошибка  | Отн.ошибка\n");
    printf("------|-------|--------|--------|---------|------------\n");
    
    for (int i = 0; i < N; i++) 
    {
        double Q_pred = A_par * s[i] * s[i] + B_par * s[i] + C_par;
        double error = Q[i] - Q_pred;
        double rel_error = fabs(error / Q[i]) * 100;
        
        SSE_quad += error * error;
        sum_abs_err_quad += fabs(error);
        sum_rel_err_quad += rel_error;
        
        printf("  %d   | %.2f  | %.3f  | %.3f  | %7.3f | %6.2f%%\n",
               i+1, s[i], Q[i], Q_pred, error, rel_error);
    }
    
    double R_squared = 1 - (SSE_quad / SST);
    double R_index = sqrt(R_squared);
    
    printf("\nИндекс корреляции R = %.4f\n", R_index);
    printf("R² (коэффициент детерминации) = %.4f\n\n", R_squared);
    
    double MSE_quad = SSE_quad / N;
    double RMSE_quad = sqrt(MSE_quad);
    double MAE_quad = sum_abs_err_quad / N;
    double MARE_quad = sum_rel_err_quad / N;
    
    printf("Суммарная квадратичная ошибка (SSE): %.6f\n", SSE_quad);
    printf("Средняя квадратичная ошибка (MSE):    %.6f\n", MSE_quad);
    printf("Корень из MSE (RMSE):                 %.6f\n", RMSE_quad);
    printf("Средняя абсолютная ошибка (MAE):      %.6f\n", MAE_quad);
    printf("Средняя относительная ошибка:         %.2f%%\n\n", MARE_quad);
    
    return 0;
}

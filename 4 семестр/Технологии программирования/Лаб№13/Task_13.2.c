/*
В результате эксперимента была определена некоторая табличная
зависимость. Вычислить ожидаемое значение функции в указанных точ-
ках. Построить график, на котором изобразить экспериментальные точки,
график интерполяционной зависимости, ожидаемое значение в указанных
точках. Реализовать следующие методы интерполяции:
⁡⁢⁢⁣•интерполяционный полином Лагранжа;
•интерполяционный полином Ньютона;
•канонический полином;
•функцию линейной интерполяции;
•функцию сплайн-интерполяции.⁡
Написать программу для решения задачи. Исходные данные для
программы хранятся в файле. Структуру файла разработать самостоя-
тельно. Решение проверить с помощью известного Вам математического
пакета.
x1 = 0.896
x2 = 0.774
x3 = 0.955

x   0.68    0.73    0.80    0.88    0.93   0.99
y 0.80866 0.89492 1.02964 1.20966 1.34087 1.52368
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Структура для хранения данных
typedef struct {
    int n;           // количество экспериментальных точек
    double *x;       // массив x-координат
    double *y;       // массив y-координат
    int m;           // количество точек для интерполяции
    double *x_interp; // x-координаты для интерполяции
} Data;

// Ф-я для чтения данных из файла
Data* read_data(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла!");
        return NULL;
    }

    Data *data = (Data*)malloc(sizeof(Data));

    fscanf(file, "%d", &data->n);

    data->x = (double*)malloc(data->n * sizeof(double));
    data->y = (double*)malloc(data->n * sizeof(double));

    // Читаем экспериментальные данные
    for (int i = 0; i < data->n; i++)
        fscanf(file, "%lf %lf", &data->x[i], &data->y[i]);

    // количество точек для интерполяции
    fscanf(file, "%d", &data->m);

    // выделяем память и читаем точки для интерполяции
    data->x_interp = (double*)malloc(data->m * sizeof(double));
    for (int i = 0; i < data->m; i++)
        fscanf(file, "%lf", &data->x_interp[i]);

    fclose(file);
    return data;
}

// Ф-я для освобождения памяти
void free_data(Data *data) 
{
    if (data) {
        free(data->x);
        free(data->y);
        free(data->x_interp);
        free(data);
    }
}

// Интерполяционный полином Лагранжа
double lagrange_interpolation(Data *data, double t) 
{
    double result = 0.0;

    // Проходим по всем точкам
    for (int i = 0; i < data->n; i++) 
    {
        double term = data->y[i]; 

        for (int j = 0; j < data->n; j++) 
            if (j != i) 
                term *= (t - data->x[j]) / (data->x[i] - data->x[j]);

        result += term;
    }
    return result;
}

// Интерполяционный полином Ньютона
double newton_interpolation(Data *data, double t) 
{
    int n = data->n;

    // Создаем таблицу разделенных разностей
    double **C = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        C[i] = (double*)malloc(n * sizeof(double));
        C[i][0] = data->y[i];  // Первый столбец - значения y
    }

    // Вычисляем разделенные разности
    for (int j = 1; j < n; j++) 
        for (int i = j; i < n; i++) 
            C[i][j] = (C[i][j-1] - C[i-1][j-1]) / (data->x[i] - data->x[i-j]);

    // Вычисляем значение полинома Ньютона
    double result = C[0][0];  // первый коэффициент
    double prod = 1.0;

    for (int i = 1; i < n; i++) {
        prod *= (t - data->x[i-1]);
        result += C[i][i] * prod;
    }

    for (int i = 0; i < n; i++)
        free(C[i]);
    free(C);

    return result;
}

// Канонический полином
double canonical_polynomial(Data *data, double t) 
{
    int n = data->n;

    // Создаем расширенную матрицу системы
    double **A = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) 
    {
        A[i] = (double*)malloc((n + 1) * sizeof(double));

        // Заполняем матрицу
        for (int j = 0; j < n; j++)
            A[i][j] = pow(data->x[i], j);

        // Правая часть
        A[i][n] = data->y[i];
    }

    // Решаем систему методом Гаусса
    for (int k = 0; k < n; k++) 
    {
        // Прямой ход
        for (int i = k + 1; i < n; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j <= n; j++)
                A[i][j] -= factor * A[k][j];
        }
    }

    // Обратный ход
    double *a = (double*)malloc(n * sizeof(double));
    for (int i = n - 1; i >= 0; i--) 
    {
        a[i] = A[i][n];
        for (int j = i + 1; j < n; j++) 
            a[i] -= A[i][j] * a[j];
        a[i] /= A[i][i];
    }

    // Вычисляем значение полинома
    double result = 0.0;
    for (int i = 0; i < n; i++)
        result += a[i] * pow(t, i);

    // Освобождаем память
    for (int i = 0; i < n; i++)
        free(A[i]);
    free(A);
    free(a);

    return result;
}

// Линейная интерполяция
double linear_interpolation(Data *data, double t) 
{
    // Находим интервал [x[i], x[i+1]], в который попадает t
    int i = 0; // Начинаем с [0, 1]

    // Если t за пределами диапазона
    if (t <= data->x[0])
        i = 0;
    else if (t >= data->x[data->n - 1])
        i = data->n - 2;
    else 
        // Ищем подходящий интервал
        for (i = 0; i < data->n - 1; i++)
            if (t >= data->x[i] && t <= data->x[i + 1])
                break;
    
    double result = data->y[i] + (data->y[i + 1] - data->y[i]) * 
                    (t - data->x[i]) / (data->x[i + 1] - data->x[i]);
// y[i] значение в левой границе интервала
// Δy = y[i+1] - y[i] прирост функции на интервале
// h = x[i+1] - x[i] длина интервала
// (t - x[i]) / h локальная координата t_local ∈ [0, 1]
    return result;
}

// кубическая сплайн-интерполяция 
double* calculate_spline_coefficients(Data *data, double **b, double **c, double **d) 
{
    int n = data->n;

    *b = (double*)malloc(n * sizeof(double));
    *c = (double*)malloc(n * sizeof(double));
    *d = (double*)malloc(n * sizeof(double));

    // Массивы для решения трехдиагональной системы
    double *h = (double*)malloc(n * sizeof(double));
    double *alpha = (double*)malloc(n * sizeof(double));
    double *l = (double*)malloc(n * sizeof(double));
    double *mu = (double*)malloc(n * sizeof(double));
    double *z = (double*)malloc(n * sizeof(double));

    // Вычисляем шаги h[i] = x[i+1] - x[i]
    for (int i = 0; i < n - 1; i++)
        h[i] = data->x[i + 1] - data->x[i];

    // Вычисляем alpha[i]
    for (int i = 1; i < n - 1; i++)
        alpha[i] = 3.0 * (data->y[i + 1] - data->y[i]) / h[i] - 
                   3.0 * (data->y[i] - data->y[i - 1]) / h[i - 1];

    // Решаем трехдиагональную систему
    l[0] = 1.0;
    mu[0] = 0.0;
    z[0] = 0.0;

    for (int i = 1; i < n - 1; i++) {
        l[i] = 2.0 * (data->x[i + 1] - data->x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n - 1] = 1.0;
    z[n - 1] = 0.0;
    (*c)[n - 1] = 0.0;

    // Обратная подстановка
    for (int j = n - 2; j >= 0; j--) 
    {
        (*c)[j] = z[j] - mu[j] * (*c)[j + 1];
        (*b)[j] = (data->y[j + 1] - data->y[j]) / h[j] - 
                  h[j] * ((*c)[j + 1] + 2.0 * (*c)[j]) / 3.0;
        (*d)[j] = ((*c)[j + 1] - (*c)[j]) / (3.0 * h[j]);
    }

    // Освобождаем временные массивы
    free(h);
    free(alpha);
    free(l);
    free(mu);
    free(z);

    return *b;
}

double spline_interpolation(Data *data, double t) 
{
    double *b, *c, *d;
    calculate_spline_coefficients(data, &b, &c, &d);

    // Находим интервал
    int i = 0;
    if (t <= data->x[0])
        i = 0;
    else if (t >= data->x[data->n - 1])
        i = data->n - 2;
    else 
        for (i = 0; i < data->n - 1; i++) 
            if (t >= data->x[i] && t <= data->x[i + 1]) 
                break;

    // Вычисляем значение сплайна
    double dx = t - data->x[i];
    double result = data->y[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;

    // Освобождаем память
    free(b);
    free(c);
    free(d);

    return result;
}

int main() 
{
    Data *data = read_data("data_13.2.txt");
    if (!data)
        return 1;

    printf("Загружено %d экспериментальных точек\n", data->n);
    printf("Точки для интерполяции: %d\n\n", data->m);

    printf("%-15s      %-15s      %-15s      %-15s      %-15s       %-15s\n", "Точка", "Лагранж", "Ньютон", "Канонич.", "Линейная", "Сплайн");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < data->m; i++) 
    {
        double t = data->x_interp[i];
        printf("x = %-10.3f%-15.6f%-15.6f%-15.6f%-15.6f%-15.6f\n",
               t,
               lagrange_interpolation(data, t),
               newton_interpolation(data, t),
               canonical_polynomial(data, t),
               linear_interpolation(data, t),
               spline_interpolation(data, t));
    }

    free_data(data);
    return 0;
}

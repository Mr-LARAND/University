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

// Функция для чтения данных из файла
Data* read_data(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла %s\n", filename);
        return NULL;
    }

    Data *data = (Data*)malloc(sizeof(Data));

    // Читаем количество экспериментальных точек
    fscanf(file, "%d", &data->n);

    // Выделяем память для массивов
    data->x = (double*)malloc(data->n * sizeof(double));
    data->y = (double*)malloc(data->n * sizeof(double));

    // Читаем экспериментальные данные
    for (int i = 0; i < data->n; i++) {
        fscanf(file, "%lf %lf", &data->x[i], &data->y[i]);
    }

    // Читаем количество точек для интерполяции
    fscanf(file, "%d", &data->m);

    // Выделяем память и читаем точки для интерполяции
    data->x_interp = (double*)malloc(data->m * sizeof(double));
    for (int i = 0; i < data->m; i++) {
        fscanf(file, "%lf", &data->x_interp[i]);
    }

    fclose(file);
    return data;
}

// Функция для освобождения памяти
void free_data(Data *data) {
    if (data) {
        free(data->x);
        free(data->y);
        free(data->x_interp);
        free(data);
    }
}

// 1. Интерполяционный полином Лагранжа
double lagrange_interpolation(Data *data, double t) {
    double result = 0.0;

    // Проходим по всем точкам
    for (int i = 0; i < data->n; i++) {
        double term = data->y[i];  // Начинаем с y_i

        // Вычисляем произведение (t - x_j) / (x_i - x_j) для всех j != i
        for (int j = 0; j < data->n; j++) {
            if (j != i) {
                term *= (t - data->x[j]) / (data->x[i] - data->x[j]);
            }
        }

        result += term;
    }

    return result;
}

// 2. Интерполяционный полином Ньютона
double newton_interpolation(Data *data, double t) {
    int n = data->n;

    // Создаем таблицу разделенных разностей
    double **C = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        C[i] = (double*)malloc(n * sizeof(double));
        C[i][0] = data->y[i];  // Первый столбец - значения y
    }

    // Вычисляем разделенные разности
    for (int j = 1; j < n; j++) {
        for (int i = j; i < n; i++) {
            C[i][j] = (C[i][j-1] - C[i-1][j-1]) / (data->x[i] - data->x[i-j]);
        }
    }

    // Вычисляем значение полинома Ньютона
    double result = C[0][0];  // Первый коэффициент
    double prod = 1.0;

    for (int i = 1; i < n; i++) {
        prod *= (t - data->x[i-1]);
        result += C[i][i] * prod;
    }

    // Освобождаем память
    for (int i = 0; i < n; i++) {
        free(C[i]);
    }
    free(C);

    return result;
}

// 3. Канонический полином (через решение системы линейных уравнений)
double canonical_polynomial(Data *data, double t) {
    int n = data->n;

    // Создаем расширенную матрицу системы [A|b]
    double **A = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        A[i] = (double*)malloc((n + 1) * sizeof(double));

        // Заполняем матрицу Вандермонда
        for (int j = 0; j < n; j++) {
            A[i][j] = pow(data->x[i], j);
        }

        // Правая часть
        A[i][n] = data->y[i];
    }

    // Решаем систему методом Гаусса
    for (int k = 0; k < n; k++) {
        // Прямой ход
        for (int i = k + 1; i < n; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j <= n; j++) {
                A[i][j] -= factor * A[k][j];
            }
        }
    }

    // Обратный ход - находим коэффициенты
    double *a = (double*)malloc(n * sizeof(double));
    for (int i = n - 1; i >= 0; i--) {
        a[i] = A[i][n];
        for (int j = i + 1; j < n; j++) {
            a[i] -= A[i][j] * a[j];
        }
        a[i] /= A[i][i];
    }

    // Вычисляем значение полинома P(t) = a0 + a1*t + a2*t^2 + ... + an*t^n
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += a[i] * pow(t, i);
    }

    // Освобождаем память
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(a);

    return result;
}

// 4. Линейная интерполяция
double linear_interpolation(Data *data, double t) {
    // Находим интервал [x[i], x[i+1]], в который попадает t
    int i = 0;

    // Если t за пределами диапазона
    if (t <= data->x[0]) {
        i = 0;
    } else if (t >= data->x[data->n - 1]) {
        i = data->n - 2;
    } else {
        // Ищем подходящий интервал
        for (i = 0; i < data->n - 1; i++) {
            if (t >= data->x[i] && t <= data->x[i + 1]) {
                break;
            }
        }
    }

    // Линейная интерполяция: y = y[i] + (y[i+1] - y[i]) * (t - x[i]) / (x[i+1] - x[i])
    double result = data->y[i] + (data->y[i + 1] - data->y[i]) * 
                    (t - data->x[i]) / (data->x[i + 1] - data->x[i]);

    return result;
}

// 5. Сплайн-интерполяция (кубический сплайн)
double* calculate_spline_coefficients(Data *data, double **b, double **c, double **d) {
    int n = data->n;

    // Выделяем память для коэффициентов
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
    for (int i = 0; i < n - 1; i++) {
        h[i] = data->x[i + 1] - data->x[i];
    }

    // Вычисляем alpha[i]
    for (int i = 1; i < n - 1; i++) {
        alpha[i] = 3.0 * (data->y[i + 1] - data->y[i]) / h[i] - 
                   3.0 * (data->y[i] - data->y[i - 1]) / h[i - 1];
    }

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
    for (int j = n - 2; j >= 0; j--) {
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

double spline_interpolation(Data *data, double t) {
    double *b, *c, *d;
    calculate_spline_coefficients(data, &b, &c, &d);

    // Находим интервал
    int i = 0;
    if (t <= data->x[0]) {
        i = 0;
    } else if (t >= data->x[data->n - 1]) {
        i = data->n - 2;
    } else {
        for (i = 0; i < data->n - 1; i++) {
            if (t >= data->x[i] && t <= data->x[i + 1]) {
                break;
            }
        }
    }

    // Вычисляем значение сплайна
    double dx = t - data->x[i];
    double result = data->y[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;

    // Освобождаем память
    free(b);
    free(c);
    free(d);

    return result;
}

// Функция для записи результатов в файл
void write_results(Data *data, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка создания файла %s\n", filename);
        return;
    }

    fprintf(file, "Результаты интерполяции\n");
    fprintf(file, "========================\n\n");

    fprintf(file, "Экспериментальные данные:\n");
    for (int i = 0; i < data->n; i++) {
        fprintf(file, "x[%d] = %.5f, y[%d] = %.5f\n", i, data->x[i], i, data->y[i]);
    }

    fprintf(file, "\nТочки для интерполяции: x1 = %.3f, x2 = %.3f, x3 = %.3f\n\n", 
            data->x_interp[0], data->x_interp[1], data->x_interp[2]);

    fprintf(file, "%-15s%-15s%-15s%-15s%-15s%-15s\n", 
            "Точка", "Лагранж", "Ньютон", "Канонич.", "Линейная", "Сплайн");
    fprintf(file, "--------------------------------------------------------------------------\n");

    for (int i = 0; i < data->m; i++) {
        double t = data->x_interp[i];
        fprintf(file, "x = %-10.3f%-15.6f%-15.6f%-15.6f%-15.6f%-15.6f\n",
                t,
                lagrange_interpolation(data, t),
                newton_interpolation(data, t),
                canonical_polynomial(data, t),
                linear_interpolation(data, t),
                spline_interpolation(data, t));
    }

    fclose(file);
    printf("Результаты записаны в файл %s\n", filename);
}

int main() 
{
    printf("Программа интерполяции\n");
    printf("======================\n\n");

    // Читаем данные из файла
    Data *data = read_data("data_13.2.txt");
    if (!data) {
        return 1;
    }

    printf("Загружено %d экспериментальных точек\n", data->n);
    printf("Точки для интерполяции: %d\n\n", data->m);

    // Выводим результаты на экран
    printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", 
           "Точка", "Лагранж", "Ньютон", "Канонич.", "Линейная", "Сплайн");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < data->m; i++) {
        double t = data->x_interp[i];
        printf("x = %-10.3f%-15.6f%-15.6f%-15.6f%-15.6f%-15.6f\n",
               t,
               lagrange_interpolation(data, t),
               newton_interpolation(data, t),
               canonical_polynomial(data, t),
               linear_interpolation(data, t),
               spline_interpolation(data, t));
    }

    // Записываем результаты в файл
    write_results(data, "results.txt");
    free_data(data);
    return 0;
}

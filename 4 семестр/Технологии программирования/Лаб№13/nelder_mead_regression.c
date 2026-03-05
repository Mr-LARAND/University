/*
 * МЕТОД НЕЛДЕРА-МИДА (ДЕФОРМИРУЕМОГО МНОГОГРАННИКА)
 * Для подбора квадратичной зависимости Q(s) = A*s² + B*s + C
 * 
 * Алгоритм:
 * 1. Создаем начальный симплекс (4 вершины для 3 параметров)
 * 2. На каждой итерации:
 *    - Находим лучшую, худшую и вторую худшую вершины
 *    - Вычисляем центроид (среднее) лучших вершин
 *    - Пробуем операции: отражение, растяжение, сжатие, редукция
 * 3. Останавливаемся при достижении заданной точности
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define DIMENSION 9  // количество точек данных
#define DIM 3  // размерность (A, B, C)
#define MAX_ITER 10000  // максимум итераций
#define EPSILON 1e-8  // точность
#define ALPHA 1.0   // коэффициент отражения
#define GAMMA 2.0   // коэффициент растяжения
#define BETTA 0.5     // коэффициент сжатия
#define SIGMA 0.5   // коэффициент редукции

// Структура для хранения данных
typedef struct {
    double s[DIMENSION];  // независимая переменная
    double Q[DIMENSION];  // зависимая переменная
    int n;        // количество точек
} Data;

// Структура для вершины симплекса
typedef struct {
    double params[DIM];  // параметры [A, B, C]
    double value;        // значение целевой функции 
} Vertex;

// f(A, B, C) = SSE(A, B, C) = Σ(Qᵢ - (A·sᵢ² + B·sᵢ + C))²
double objective_function(double *params, Data *data) 
{
    double A = params[0];
    double B = params[1];
    double C = params[2];

    double sse = 0.0;
    for (int i = 0; i < data->n; i++) {
        double s_i = data->s[i];
        double Q_predicted = A * s_i * s_i + B * s_i + C;
        double error = data->Q[i] - Q_predicted;
        sse += error * error;
    }

    return sse;
}

void copy_array(double *dest, double *src, int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

// Вычисление среднего всех вершин кроме худшей (worst)
void compute_centroid(Vertex *simplex, int exclude_idx, double *centroid) 
{
    for (int i = 0; i < DIM; i++)
        centroid[i] = 0.0;

    for (int i = 0; i < DIM + 1; i++) 
        if (i != exclude_idx) {
            for (int j = 0; j < DIM; j++)
                centroid[j] += simplex[i].params[j];
        }
    
    for (int i = 0; i < DIM; i++)
        centroid[i] /= DIM;
}

// Отражение точки относительно центроида
void reflect(double *centroid, double *worst, double *reflected, double alpha) 
{
    for (int i = 0; i < DIM; i++)
        reflected[i] = centroid[i] + alpha * (centroid[i] - worst[i]);
}

// Растяжение
void expand(double *centroid, double *reflected, double *expanded, double gamma) 
{
    for (int i = 0; i < DIM; i++)
        expanded[i] = centroid[i] + gamma * (reflected[i] - centroid[i]);
}

// Сжатие
void contract(double *centroid, double *worst, double *contracted, double rho) 
{
    for (int i = 0; i < DIM; i++)
        contracted[i] = centroid[i] + rho * (worst[i] - centroid[i]);
}

// Редукция симплекса к лучшей точке
void shrink(Vertex *simplex, int best_idx, double sigma, Data *data) 
{
    for (int i = 0; i < DIM + 1; i++)
        if (i != best_idx) {
            for (int j = 0; j < DIM; j++) 
                simplex[i].params[j] = simplex[best_idx].params[j] + 
                                       sigma * (simplex[i].params[j] - simplex[best_idx].params[j]);
            simplex[i].value = objective_function(simplex[i].params, data);
        }
}

// Проверка критерия останова
int check_convergence(Vertex *simplex, double tol) 
{
    double mean = 0.0;
    for (int i = 0; i < DIM + 1; i++)
        mean += simplex[i].value;
    mean /= (DIM + 1);

    double variance = 0.0;
    for (int i = 0; i < DIM + 1; i++) {
        double diff = simplex[i].value - mean;
        variance += diff * diff;
    }
    variance /= (DIM + 1);

    return sqrt(variance) < tol;
}

void nelder_mead(double *initial_params, Data *data, double *result) 
{
    Vertex simplex[DIM + 1];

    // Первая вершина - начальное приближение
    copy_array(simplex[0].params, initial_params, DIM);
    simplex[0].value = objective_function(simplex[0].params, data);

    // Остальные вершины - смещения по координатным осям
    double step = 1.0;  // размер начального шага
    for (int i = 1; i < DIM + 1; i++) {
        copy_array(simplex[i].params, initial_params, DIM);
        simplex[i].params[i - 1] += step;  // смещаем по i-й координате
        simplex[i].value = objective_function(simplex[i].params, data);
    }

    printf("Начальный симплекс: \n");
    for (int i = 0; i < DIM + 1; i++) {
        printf("  Вершина %d: [%.4f, %.4f, %.4f]\n", 
               i, simplex[i].params[0], simplex[i].params[1], 
               simplex[i].params[2]);
    }

    // Основной цикл оптимизации
    int iteration = 0;

    while (iteration < MAX_ITER) {
        // Сортировка вершин по значению функции
        for (int i = 0; i < DIM; i++) {
            for (int j = i + 1; j < DIM + 1; j++) {
                if (simplex[j].value < simplex[i].value) {
                    Vertex temp = simplex[i];
                    simplex[i] = simplex[j];
                    simplex[j] = temp;
                }
            }
        }

        int best_idx = 0;
        int worst_idx = DIM;
        int second_worst_idx = DIM - 1;

        // Проверка сходимости
        if (check_convergence(simplex, EPSILON))
            break;

        // Вычисление центроида
        double centroid[DIM];
        compute_centroid(simplex, worst_idx, centroid);

        // отражение
        double reflected[DIM];
        reflect(centroid, simplex[worst_idx].params, reflected, ALPHA);
        double reflected_value = objective_function(reflected, data);

        if (reflected_value < simplex[second_worst_idx].value && 
            reflected_value >= simplex[best_idx].value) {
            // Принимаем отраженную точку
            copy_array(simplex[worst_idx].params, reflected, DIM);
            simplex[worst_idx].value = reflected_value;
        }
        // рястяжение
        else if (reflected_value < simplex[best_idx].value) {
            double expanded[DIM];
            expand(centroid, reflected, expanded, GAMMA);
            double expanded_value = objective_function(expanded, data);

            if (expanded_value < reflected_value) {
                // Принимаем растянутую точку
                copy_array(simplex[worst_idx].params, expanded, DIM);
                simplex[worst_idx].value = expanded_value;
            } 
            else {
                // Принимаем отраженную точку
                copy_array(simplex[worst_idx].params, reflected, DIM);
                simplex[worst_idx].value = reflected_value;
            }
        }
        // сжатие
        else {
            double contracted[DIM];
            contract(centroid, simplex[worst_idx].params, contracted, BETTA);
            double contracted_value = objective_function(contracted, data);

            if (contracted_value < simplex[worst_idx].value) {
                // Принимаем сжатую точку
                copy_array(simplex[worst_idx].params, contracted, DIM);
                simplex[worst_idx].value = contracted_value;
            }
            // редукция
            else
                shrink(simplex, best_idx, SIGMA, data);
        }

        iteration++;
    }

    // Финальная сортировка
    for (int i = 0; i < DIM; i++)
        for (int j = i + 1; j < DIM + 1; j++)
            if (simplex[j].value < simplex[i].value) {
                Vertex temp = simplex[i];
                simplex[i] = simplex[j];
                simplex[j] = temp;
            }
    copy_array(result, simplex[0].params, DIM);
}

void compute_statistics(double *params, Data *data) 
{
    double A = params[0];
    double B = params[1];
    double C = params[2];

    printf("\nвадратичная зависимость: Q(s) = %.8f * s² + %.8f * s + %.8f\n\n", A, B, C);

    // Вычисление среднего Q
    double mean_Q = 0.0;
    for (int i = 0; i < data->n; i++)
        mean_Q += data->Q[i];
    mean_Q /= data->n;

    double SSE = 0.0, MAE = 0.0, MARE = 0.0, SST = 0.0;

    printf("Точка | s     | Q_изм  | Q_пред | Ошибка  | Отн.ошибка\n");
    printf("------|-------|--------|--------|---------|------------\n");

    for (int i = 0; i < data->n; i++) {
        double s_i = data->s[i];
        double Q_predicted = A * s_i * s_i + B * s_i + C;
        double error = data->Q[i] - Q_predicted;
        double abs_error = fabs(error);
        double rel_error = (abs_error / fabs(data->Q[i])) * 100.0;

        SSE += error * error;
        MAE += abs_error;
        MARE += rel_error;
        SST += (data->Q[i] - mean_Q) * (data->Q[i] - mean_Q);

        printf("  %d   | %.2f  | %.3f  | %.3f  | %7.3f | %6.2f%%\n",
               i + 1, s_i, data->Q[i], Q_predicted, error, rel_error);
    }

    double MSE = SSE / data->n;
    double RMSE = sqrt(MSE);
    MAE /= data->n;
    MARE /= data->n;

    double R_squared = 1.0 - (SSE / SST);
    double R = sqrt(R_squared);

    printf("\nМетрики качества:\n");
    printf("  SSE  (Сумма квадратов ошибок):     %.8f\n", SSE);
    printf("  MSE  (Средняя квадр. ошибка):      %.8f\n", MSE);
    printf("  RMSE (Корень из MSE):              %.8f\n", RMSE);
    printf("  MAE  (Средняя абс. ошибка):        %.8f\n", MAE);
    printf("  MARE (Средняя отн. ошибка):        %.4f%%\n", MARE);
    printf("  R    (Индекс корреляции):          %.8f\n", R);
}

int main() 
{
    Data data;
    data.n = DIMENSION;

    FILE *file = fopen("data_13.1.txt", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла data_13.1.txt\n");
        return 1;
    }

    for (int i = 0; i < DIMENSION; i++)
        if (fscanf(file, "%lf %lf", &data.s[i], &data.Q[i]) != 2) {
            printf("Ошибка чтения данных\n");
            fclose(file);
            return 1;
        }
    fclose(file);

    // Начальное приближение иожно брать любое ?
    double initial_params[DIM] = {0.0, 0.0, 0.0};  // [A, B, C]

    double result[DIM];
    nelder_mead(initial_params, &data, result);
    compute_statistics(result, &data);

    return 0;
}

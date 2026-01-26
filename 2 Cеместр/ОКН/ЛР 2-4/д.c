#include <stdio.h>
#include <math.h>

int main() {
    int k = 10;
    double x = 2.0;
    double S = 0.0;

    for (int n = 1; n <= k; n++) {
        // Вычисляем текущий член суммы
        double term = pow(-1, n) * (2 * pow(n, 2) + 1) / (8.0 * n) * pow(x, 2 * n);
        S += term; // Добавляем к сумме
    }

    printf("S = %.6f\n", S); // Выводим результат с точностью до 6 знаков после запятой
    return 0;
}

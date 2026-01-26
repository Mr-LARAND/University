#include <stdio.h>

double f(double x) {
    return x * x * x - x * x - 1; // Определение функции f(x)
}

int main() {
    double lower, upper, step;

    // Запрос границ и шага у пользователя с защитой
    printf("Enter the lower bound: ");
    while (scanf("%lf", &lower) != 1) {
        printf("Incorrect input. Please enter the number: ");
        while(getchar() != '\n'); // Очищаем ввод
    }

    printf("Enter the upper bound: ");
    while (scanf("%lf", &upper) != 1 || upper <= lower) {
        printf("Incorrect input. The upper limit should be larger than the lower one. Please enter the number: ");
        while(getchar() != '\n'); // Очищаем ввод
    }

    printf("Enter the step: ");
    while (scanf("%lf", &step) != 1 || step <= 0) {
        printf("Incorrect input. The step must be positive. Please enter the number: ");
        while(getchar() != '\n'); // Очищаем ввод
    }

    printf("\nTable of function valuesf(x) = x^3 - x^2 - 1:\n");
    printf(" x\t\t f(x)\n");
    printf("-------------------------\n");

    // Табулирование функции
    for (double x = lower; x <= upper; x += step) {
        printf("%.2f\t\t %.2f\n", x, f(x));
    }

    return 0;
}

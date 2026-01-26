#include <stdio.h>

int main() {
    int days[] = {800, 750, 600, 900, 1000, 950, 900, 830, 700, 675};
    int maxRevenue = 0;
    int countDays = 0;

    // Вычисление максимальной выручки с 3 по 9 день торговли
    for (int i = 2; i < 9; i++) {
        if (days[i] > maxRevenue) {
            maxRevenue = days[i];
        }
    }
    printf("Максимальная выручка с 3 по 9 день торговли: %d\n", maxRevenue);

    // Подсчет числа дней, когда выручка была более 600, но менее 900 руб
    for (int i = 0; i < 10; i++) {
        if (days[i] > 600 && days[i] < 900) {
            countDays++;
        }
    }
    printf("Число дней торговли, когда выручка была более 600, но менее 900 руб: %d\n", countDays);

    return 0;
}

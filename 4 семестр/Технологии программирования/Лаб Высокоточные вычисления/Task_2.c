#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include <string.h>
/**
 * @brief Реализация теста Миллера-Рабина на простоту.
 * @param n Число для проверки (mpz_t).
 * @param k Количество раундов для повышения точности.
 * @return int 1 если число, вероятно, простое, 0 если составное.
 */
int miller_rabin_test(const mpz_t n, int k) 
{
    // Базовые случаи
    if (mpz_cmp_ui(n, 2) < 0) 
        return 0; // n < 2 не простые
    if (mpz_cmp_ui(n, 3) == 0 || mpz_cmp_ui(n, 2) == 0) 
        return 1; // 2 и 3 простые
    if (mpz_even_p(n)) return 0; 
        // Четные > 2 не простые

    // Найходим d и s, где n-1 = d * 2^s, d - нечетное
    mpz_t d, n_minus_1;
    mpz_inits(d, n_minus_1, NULL); // инициализация нескольких переменных типа mpz_t
    mpz_sub_ui(n_minus_1, n, 1);
    mpz_set(d, n_minus_1); // Копируем значение n-1 в d
    unsigned long int s = mpz_scan1(d, 0); // Находит индекс первой установленной биты (эффективно для s)
    mpz_tdiv_q_2exp(d, d, s); // d = d / 2^s

    // Инициализация переменных для цикла
    mpz_t a, x;
    mpz_inits(a, x, NULL);
    gmp_randstate_t rand_state;
    gmp_randinit_default(rand_state);
    gmp_randseed_ui(rand_state, time(NULL));

    // Цикл проверки k раундов
    for (int i = 0; i < k; i++) {
        // Выбираем случайное a в диапазоне [2, n-2]
        mpz_urandomm(a, rand_state, n_minus_1); // Генерирует случайное число a в диапазоне [0, n-2]
        mpz_add_ui(a, a, 1);                    // Сдвигаем диапазон до [1, n-1]
        if (mpz_cmp_ui(a, 1) == 0) 
            mpz_add_ui(a,a,1); // если a получилось равным 1, делаем его 2


        // x = a^d mod n
        mpz_powm(x, a, d, n);

        // Если x == 1 или x == n-1, переходим к следующей итерации
        if (mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, n_minus_1) == 0)
            continue;

        // Повторяем s-1 раз
        int is_composite = 1;
        for (unsigned long int r = 0; r < s; r++) {
            // x = x^2 mod n
            mpz_powm_ui(x, x, 2, n);
            if (mpz_cmp(x, n_minus_1) == 0) {
                is_composite = 0;
                break; // Свидетель не найден, число может быть простым
            }
        }

        if (is_composite) {
            mpz_clears(d, n_minus_1, a, x, NULL);
            gmp_randclear(rand_state);
            return 0; // Число точно составное
        }
    }

    mpz_clears(d, n_minus_1, a, x, NULL);
    gmp_randclear(rand_state);
    return 1; // Число, вероятно, простое
}

/**
 * @brief Классический тест на простоту
 * @param n Число для проверки (mpz_t)
 * @return 1 если число простое, 0 если составное
 */
int trial_division_test(const mpz_t n) 
{
    // Базовые случаи
    if (mpz_cmp_ui(n, 2) < 0) 
        return 0;
    if (mpz_cmp_ui(n, 3) == 0 || mpz_cmp_ui(n, 2) == 0) 
        return 1;
    if (mpz_even_p(n)) 
        return 0;

    mpz_t sqrt_n, i;
    mpz_inits(sqrt_n, i, NULL);
    mpz_sqrt(sqrt_n, n); // Вычисляем корень из n

    // Проверяем делители от 3 до sqrt(n) с шагом 2
    for (mpz_set_ui(i, 3); mpz_cmp(i, sqrt_n) <= 0; mpz_add_ui(i, i, 2))
        if (mpz_divisible_p(n, i)) {
            mpz_clears(sqrt_n, i, NULL);
            return 0; // Найден делитель, число составное
        }

    mpz_clears(sqrt_n, i, NULL);
    return 1; // Делителей не найдено, число простое
}

int main() 
{
    int run_time_test = 1;

    int KN = 100; // Минимальная длина числа
    int KK = 150; // Максимальная длина числа
    int Z = 10;  // Общее количество чисел для генерации (должно быть четным)
    int MILLER_RABIN_ROUNDS = 25; // Количество раундов для теста Миллера-Рабина

    mpz_t number_set[Z]; // Массив для хранения сгенерированных чисел

    gmp_randstate_t rand_state;
    gmp_randinit_default(rand_state);
    srand(time(NULL));
    gmp_randseed_ui(rand_state, time(NULL) + rand());

    printf("Генерация %d простых и %d составных чисел\n", Z / 2, Z / 2);

    // Генерация Z/2 простых чисел 
    for (int i = 0; i < Z / 2; i++) 
    {
        mpz_init(number_set[i]);
        mpz_t startt, endd, n, range;
        mpz_inits(startt, endd, n, range, NULL);
        
        int p = rand() % (KK - KN + 1) + KN; // Случайная длина
        mpz_ui_pow_ui(startt, 10, p - 1);
        mpz_ui_pow_ui(endd, 10, p);
        mpz_sub(range, endd, startt);

        do {
            mpz_urandomm(n, rand_state, range);
            mpz_add(n, n, startt);
        } while (mpz_probab_prime_p(n, MILLER_RABIN_ROUNDS) == 0); // Используем встроенный для быстрой генерации

        mpz_set(number_set[i], n);
        gmp_printf("Сгенерировано простое %d: %Zd\n", i + 1, number_set[i]);
        mpz_clears(startt, endd, n, range, NULL);
    }

    // Генерация Z/2 составных чисел
    for (int i = Z / 2; i < Z; i++) 
    {
        mpz_init(number_set[i]);
        mpz_t factor1, factor2, startt, endd, range;
        mpz_inits(factor1, factor2, startt, endd, range, NULL);

        int p = rand() % (KK - KN + 1) + KN; // Случайная длина
        int p1_len = p / 2;
        int p2_len = p - p1_len;

        // Генерируем два множителя
        mpz_ui_pow_ui(startt, 10, p1_len - 1);
        mpz_ui_pow_ui(endd, 10, p1_len);
        mpz_sub(range, endd, startt);
        mpz_urandomm(factor1, rand_state, range);
        mpz_add(factor1, factor1, startt);

        mpz_ui_pow_ui(startt, 10, p2_len - 1);
        mpz_ui_pow_ui(endd, 10, p2_len);
        mpz_sub(range, endd, startt);
        mpz_urandomm(factor2, rand_state, range);
        mpz_add(factor2, factor2, startt);

        mpz_mul(number_set[i], factor1, factor2); // Перемножаем
        gmp_printf("Сгенерировано составное %d: %Zd\n", i + 1, number_set[i]);
        mpz_clears(factor1, factor2, startt, endd, range, NULL);
    }
    
    printf("\nПроверка сгенерированных чисел с помощью реализованного теста Миллера-Рабина\n");

    for (int i = 0; i < Z; i++) 
    {
        int is_prime = miller_rabin_test(number_set[i], MILLER_RABIN_ROUNDS);
        gmp_printf("Число %d (%s) - %s\n", 
            i + 1, 
            (i < Z/2) ? "ожидается простое" : "ожидается составное", 
            is_prime ? "вероятно простое" : "составное");
    }

    
    printf("\nСравнение времени выполнения тестов для одного числа\n");
    // Выбираем последнее сгенерированное составное число для теста
    mpz_t test_num;
    mpz_init_set(test_num, number_set[Z-1]);

    gmp_printf("Тестируемое число: %Zd\n", test_num);

    clock_t start, end;
    double cpu_time_used;

    // Тест Миллера-Рабина
    start = clock();
    int mr_result = miller_rabin_test(test_num, MILLER_RABIN_ROUNDS);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Тест Миллера-Рабина (%d раундов) завершился за %f секунд. Результат: %s\n",
            MILLER_RABIN_ROUNDS, cpu_time_used, mr_result ? "ПРОСТОЕ" : "СОСТАВНОЕ");

    // Классический тест
    start = clock();
    int td_result = trial_division_test(test_num);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Классический тест (пробное деление) завершился за %f секунд. Результат: %s\n",
        cpu_time_used, td_result ? "ПРОСТОЕ" : "СОСТАВНОЕ");
               
    mpz_clear(test_num);

    // Очистка памяти
    for (int i = 0; i < Z; i++)
        mpz_clear(number_set[i]);
    gmp_randclear(rand_state);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <quadmath.h>

// Создание директории (кроссплатформенно)
void make_dir(const char* name) {
#ifdef _WIN32
    mkdir(name);
#else
    mkdir(name, 0777);
#endif
}

void copy_array(int* original, int* copy_arr, int bits) {
    for (int i = 0; i < bits; i++) {
        copy_arr[i] = original[i];
    }
}

void dec_to_bin(int number, int* massiv, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        massiv[i] = number % 2;
        number /= 2;
    }
}

int bin_to_dec(int* number_in_bin, int bits) {
    int number = 0;
    for (int i = 0; i < bits; i++) {
        number = number * 2 + number_in_bin[i];
    }
    return number;
}

// Перевод из __float128 в двоичный массив (IEEE 754)
void transfer_to_bin(__float128 number, int* number_in_bin, int bits) {
    int znak, exponent_size, mantissa_size, exp_bias;
    if (bits == 32) { exponent_size = 8; mantissa_size = 23; exp_bias = 127; }
    else if (bits == 64) { exponent_size = 11; mantissa_size = 52; exp_bias = 1023; }
    else { exponent_size = 15; mantissa_size = 112; exp_bias = 16383; }

    if (number < 0) { znak = 1; number = -number; }
    else znak = 0;

    // Обработка нуля
    if (number == 0.0Q) {
        for (int i = 0; i < bits; i++) number_in_bin[i] = 0;
        number_in_bin[0] = znak;
        return;
    }

    int e = (int)floorq(log2q(number));
    int exp_val = e + exp_bias;

    int *exponent = (int*)calloc(exponent_size, sizeof(int));
    dec_to_bin(exp_val, exponent, exponent_size);

    __float128 double_mantissa = number / powq(2.0Q, (__float128)e) - 1.0Q;
    int *mantissa = (int*)calloc(mantissa_size, sizeof(int));

    for (int i = 0; i < mantissa_size; i++) {
        double_mantissa *= 2.0Q;
        if (double_mantissa >= 1.0Q) {
            mantissa[i] = 1;
            double_mantissa -= 1.0Q;
        } else {
            mantissa[i] = 0;
        }
    }

    number_in_bin[0] = znak;
    copy_array(exponent, number_in_bin + 1, exponent_size);
    copy_array(mantissa, number_in_bin + exponent_size + 1, mantissa_size);

    free(exponent);
    free(mantissa);
}

// Перевод из двоичного массива обратно в __float128
__float128 transfer_to_dec(int* number_in_bin, int bits) {
    int exponent_size, mantissa_size, exp_bias;
    if (bits == 32) { exponent_size = 8; mantissa_size = 23; exp_bias = 127; }
    else if (bits == 64) { exponent_size = 11; mantissa_size = 52; exp_bias = 1023; }
    else { exponent_size = 15; mantissa_size = 112; exp_bias = 16383; }

    // Проверка на ноль
    int all_zero = 1;
    for (int i = 1; i < bits; i++) {
        if (number_in_bin[i] != 0) {
            all_zero = 0;
            break;
        }
    }
    if (all_zero) {
        return 0.0Q;
    }

    int *exponent_arr = (int*)calloc(exponent_size, sizeof(int));
    copy_array(number_in_bin + 1, exponent_arr, exponent_size);
    int e = bin_to_dec(exponent_arr, exponent_size) - exp_bias;
    free(exponent_arr);

    __float128 double_mantissa = 1.0Q;
    for (int i = 0; i < mantissa_size; i++) {
        if (number_in_bin[i + exponent_size + 1] == 1) {
            double_mantissa += powq(2.0Q, -(__float128)(i + 1));
        }
    }

    __float128 res = double_mantissa * powq(2.0Q, (__float128)e);
    if (number_in_bin[0] == 1) res = -res;
    return res;
}

int main() {
    const char* input_file = "input.txt";
    FILE *cfg = fopen(input_file, "r");
    if (!cfg) {
        fprintf(stderr, "Ошибка: Не удалось открыть файл %s\n", input_file);
        return 1;
    }

    int n, k, bits, p;
    char a_s[128], b_s[128];
    if (fscanf(cfg, "%d %d %d %s %s %d", &n, &k, &bits, a_s, b_s, &p) != 6) {
        fprintf(stderr, "Ошибка: Неверный формат данных в %s\n", input_file);
        fclose(cfg);
        return 1;
    }
    fclose(cfg);

    __float128 a = strtoflt128(a_s, NULL);
    __float128 b = strtoflt128(b_s, NULL);

    srand(time(NULL));
    make_dir("Tasks");
    make_dir("Check");

    for (int v = 1; v <= n; v++) {char task_p[64], check_p[64], val_rounded_s[128], diff_s[64];
        sprintf(task_p, "Tasks/variant_%d.md", v);
        sprintf(check_p, "Check/variant_%d_ans.md", v);

        FILE *ft = fopen(task_p, "w");
        FILE *fc = fopen(check_p, "w");

        if (!ft || !fc) {
            fprintf(stderr, "Ошибка создания файлов для варианта %d\n", v);
            return 1;
        }

        fprintf(ft, "## Вариант %d (%d бит)\n\n| № | Число |\n|---|---|\n", v, bits);
        fprintf(fc, "## Ответы %d\n\n| № | Исходное число | Округлённое число | Биты | Погрешность |\n|---|---|---|---|---|\n", v);

        for (int i = 1; i <= k; i++) {
            // Генерация случайного числа
            __float128 r_part = 0;
            __float128 div = 1.0Q;
            for (int j = 0; j < 8; j++) {
                div *= ((__float128)RAND_MAX + 1.0Q);
                r_part += (__float128)rand() / div;
            }
            __float128 val_original = a + r_part * (b - a);

            // Округление до p знаков для задания
            quadmath_snprintf(val_rounded_s, sizeof(val_rounded_s), "%.*Qf", p, val_original);
            __float128 val_rounded = strtoflt128(val_rounded_s, NULL);

            // Перевод в биты
            int *bin = (int*)calloc(bits, sizeof(int));
            transfer_to_bin(val_rounded, bin, bits);

            // Восстановление из битов
            __float128 restored = transfer_to_dec(bin, bits);

            // Погрешность между исходным и восстановленным числом
            __float128 diff = fabsq(val_original - restored);
            quadmath_snprintf(diff_s, sizeof(diff_s), "%.2Qe", diff);

            // Преобразуем исходное число в строку
            char val_original_s[128];
            quadmath_snprintf(val_original_s, sizeof(val_original_s), "%.10Qf", val_original);

            // Запись в файлы
            fprintf(ft, "| %d | %s |\n", i, val_rounded_s);
            fprintf(fc, "| %d | %s | %s | `", i, val_original_s, val_rounded_s);
            
            for (int j = 0; j < bits; j++) {
                fprintf(fc, "%d", bin[j]);
                // Разделители для наглядности
                if ((bits == 128 && j == 0) || (bits == 128 && j == 15) ||
                    (bits == 64 && j == 0) || (bits == 64 && j == 11) ||
                    (bits == 32 && j == 0) || (bits == 32 && j == 8)) {
                    fprintf(fc, " ");
                }
            }
            fprintf(fc, "` | %s |\n", diff_s);

            free(bin);
        }
        fclose(ft);
        fclose(fc);
    }

    printf("Готово! Проверь папки Tasks и Check.\n");
    return 0;
}
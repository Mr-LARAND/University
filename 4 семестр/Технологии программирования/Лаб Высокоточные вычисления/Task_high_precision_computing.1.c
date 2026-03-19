#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <math.h>

void float_to_bin(float value, int bits[32]) 
{
    uint32_t raw;
    memcpy(&raw, &value, sizeof(float));

    for (int i = 31; i >= 0; i--) 
        bits[31 - i] = (raw >> i) & 1;
}

void double_to_bin(double value, int bits[64]) 
{
    uint64_t raw;
    memcpy(&raw, &value, sizeof(double));

    for (int i = 63; i >= 0; i--)
        bits[63 - i] = (raw >> i) & 1;
}

void long_double_to_bin(long double value, int bits[128]) 
{
    unsigned char raw[16] = {0};
    memcpy(raw, &value, sizeof(long double));

    int index = 0;
    for (int i = sizeof(long double) - 1; i >= 0; i--)
        for (int j = 7; j >= 0; j--)
            bits[index++] = (raw[i] >> j) & 1;
}

float float_to_decminal(int bits[32]) 
{
    uint32_t raw = 0;
    for (int i = 0; i < 32; i++) 
        raw = (raw << 1) | bits[i]; // Поочередно добавляем биты в raw

    float value;
    memcpy(&value, &raw, sizeof(float));
    return value;
}

double double_to_decminal(int bits[64]) 
{
    uint64_t raw = 0;
    for (int i = 0; i < 64; i++) 
        raw = (raw << 1) | bits[i];
    
    double value;
    memcpy(&value, &raw, sizeof(double));
    return value;
}

long double bin_to_long_double(int bits[128]) 
{
    unsigned char raw[16] = {0};

    int index = 0;
    for (int i = sizeof(long double) - 1; i >= 0; i--)
        for (int j = 7; j >= 0; j--)
            raw[i] |= bits[index++] << j;

    long double value;
    memcpy(&value, raw, sizeof(long double));
    return value;
}

double random_double(double a, double b) {
    return a + (double)rand() / RAND_MAX * (b - a);
}

void bits_to_string(int *bits, int size, char *str) {
    for (int i = 0; i < size; i++)
        str[i] = bits[i] + '0';
    str[size] = '\0';
}

int main() 
{
    srand(time(NULL));

    FILE *input_file = fopen("data.txt", "r");
    if (!input_file) {
        printf("Error opening file\n");
        return 1;
    }

    int input_data[6];

    for (int i = 0; i < 6; i++)
        fscanf(input_file, "%d", &input_data[i]);
    fclose(input_file);

    int n = input_data[0];   // варианты
    int k = input_data[1];   // заданий
    int bits = input_data[2]; // 32 / 64 / 128
    int a = input_data[3];    // диапазон
    int b = input_data[4];
    int p = input_data[5];   // знаков после запятой

    char format[20];
    sprintf(format, "%%.%df", p);

    for (int variant = 1; variant <= n; variant++) 
    {

        char file1_name[50], file2_name[50];
        sprintf(file1_name, "Задания/variant_%d.md", variant);
        sprintf(file2_name, "Проверка/variant_%d.md", variant);

        FILE *f1 = fopen(file1_name, "w");
        FILE *f2 = fopen(file2_name, "w");

        if (!f1 || !f2) {
            printf("Error creating output files!\n");
            return 1;
        }

        fprintf(f1, " №   Число  \n ------------ \n");
        fprintf(f2, " №   Число   Машинное представление       Точность  \n ------------------------------------------------ \n");

        for (int i = 1; i <= k; i++) 
        {
            double num = random_double(a, b);

            char num_str[50];
            sprintf(num_str, format, num);

            fprintf(f1, "  %d   %s  \n", i, num_str);

            char bin_str[200];
            long double error;

            if (bits == 32) 
            {
                int arr[32];
                float f = (float)num;

                float_to_bin(f, arr);
                bits_to_string(arr, 32, bin_str);

                float back = float_to_decminal(arr);
                error = fabsl((long double)f - back);

            } 
            else if (bits == 64) 
            {
                int arr[64];

                double_to_bin(num, arr);
                bits_to_string(arr, 64, bin_str);

                double back = double_to_decminal(arr);
                error = fabsl(num - back);

            } 
            else 
            {
                int arr[128];
                long double ld = (long double)num;

                long_double_to_bin(ld, arr);
                bits_to_string(arr, 128, bin_str);

                long double back = bin_to_long_double(arr);
                error = fabsl(ld - back);
            }

            fprintf(f2, " %d  %s  %s  %.10Le \n", i, num_str, bin_str, error);
        }

        fclose(f1);
        fclose(f2);
    }

    printf("Successfully !\n");
    return 0;
}
from random import randint, uniform
import re


# генерация целой матрицы
def get_integer_matrix(rows, cols, min_range, max_range):
    return [[randint(min_range,max_range) for _ in range(cols)] for _ in range(rows)]


# генерация вещественной матрицы
def get_real_matrix(rows, cols, min_range, max_range):
    return [[round(uniform(min_range,max_range), 2) for _ in range(cols)] for _ in range(rows)]


# вывод матрицы
def print_matrix(matrix):
    for row in matrix:
        print(row)


# Проверка для цифр и размерности матрицы:
def check_digit(count_variables):
    while True:
        result = [i for i in range(count_variables)]
        for elem in result:
            result[elem] = input(f'Введите числовое значение {elem + 1}: ')

        if all(re.match(r'^\d+$', s) for s in result) and int(result[elem]) > 1:
            result = tuple(map(int, result))
            return result
        else:
            print('Ошибка: Введите данные корректно!')


# Проверка четности N:
def even_number(number):
    while True:
        if number % 2 != 0:
            return number
        else:
            print('Порядок матрицы должен быть нечетным!\n'
                  'Программа завершила своё выполнение, для повторного ввода запустите её снова!')
            exit()


# Сортировка слиянием
def merge_list(arr_1, arr_2):  # функция слияния двух отсортированных списков
    result = []
    i = j = 0

    while i < len(arr_1) and j < len(arr_2):
        if arr_1[i] <= arr_2[j]:
            result.append(arr_1[i])
            i += 1
        else:
            result.append(arr_2[j])
            j += 1

    result.extend(arr_1[i:])
    result.extend(arr_2[j:])
    return result


def split_and_merge_list(arr):  # функция деления списка и слияния списков в общий отсортированный список
    if len(arr) <= 1:  # базовый случай рекурсии
        return arr

    mid = len(arr) // 2
    left_arr = split_and_merge_list(arr[:mid])  # рекурсивно сортируем левую половину
    right_arr = split_and_merge_list(arr[mid:])  # рекурсивно сортируем правую половину

    return merge_list(left_arr, right_arr)


# Функция нахождения максимума
def get_max(*array):
    max_elem = array[0]
    for x in range(len(array) - 1):
         if array[x+1] > max_elem: max_elem = array[x + 1]
    return max_elem


# Функция нахождения минимума
def get_min(*array):
    min_elem = array[0]
    for x in range(len(array) - 1):
         if array[x+1] < min_elem: min_elem = array[x + 1]
    return min_elem


# Функция нахождения суммы
def get_sum(*array):
    sum_elem = 0
    for x in array: sum_elem += x
    return sum_elem


# Функция нахождения суммы
def get_abs(x):
    return x if x > 0 else -x
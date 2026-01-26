import re

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
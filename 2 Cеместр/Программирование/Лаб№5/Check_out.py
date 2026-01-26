import re


# Проверка для цифр:
def check_digit(count_variables):
    while True:
        result = [i for i in range(count_variables)]
        for elem in result:
            result[elem] = input(f'Введите числовое значение {elem + 1}: ')

        if all(re.match(r'^\d+$', s) for s in result):
            result = tuple(map(int, result))
            return result
        else:
            print('Ошибка: Введите данные корректно!')



# # Проверка для букв:
# def check_letters(count_variables):
#     while True:
#         result = [i for i in range(count_variables)]
#         for elem in result:
#             result[elem] = input(f'Введите текст (только буквы): ')
#
#         if all(re.match(r'\w', s) for s in result):
#             return result
#         else:
#             print('Ошибка: Введите данные корректно!')
#
# print(check_letters())





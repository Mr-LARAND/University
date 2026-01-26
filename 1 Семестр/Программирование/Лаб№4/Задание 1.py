'''
Ларин Андрей группа 12/2
Лаб№4 Задача 1
Заполнить список из n элементов случайными целыми числами из интервала от а до b.

'''

from random import randint

while True:
    n = input('Введите кол-во элементов списка: ')
    a = input('Введите начало интервала: ')
    b = input('Введите конец интервала: ')
    if n.isdigit() and a.isdigit() and b.isdigit():
        n = int(n)
        a = int(a) + 1
        b = int(b) - 1
        if a < b:
            break
        else:
            print('Ошибка! Введите диапазон корректно!')
    else:
        print('Ошибка! Введите число (целое)!')

result = []

for i in range(n):
    random = randint(a, b)
    result.append(random)
print(f'Результат: {result}')
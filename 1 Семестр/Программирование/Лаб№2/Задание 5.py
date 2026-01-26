'''
Ларин Андрей группа 12/2
Лаб№2 Задача 5
Сгенерировать n целых случайных чисел. Определить их сумму S

'''

import random

print('\nПрограмма определяет сумму сгенерированных чисел\n')

while True:
    n = input('Введите число: ')
    if n.isdigit():
        n = int(n)
        break
    else:
        print('Ошибка! Введите число (целое)!')

res = 0
for i in range(1, n):
    s = random.randint(-10000, 10000)
    res += random.randint(-10000, 10000)
print(res)

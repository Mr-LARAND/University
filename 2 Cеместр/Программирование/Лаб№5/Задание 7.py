print('Программа находит значение выражения.\n')

import math as m
import re

while True:
    x = input('Введите числовое значение x: ')
    y = input('Введите числовое значение y: ')
    if bool(re.search(r'[-0-9]', x)) and bool(re.search(r'[-0-9]', y)):
        x = int(x)
        y = int(y)
        break
    else:
        print('Ошибка: Введите данные корректно!')

if y == 0:
    print('Ошибка: Деление на ноль!')
    exit()

if x / y > 0:
    b = m.log(x/y) + (x**2 + y)**3
if (x / y) < 0:
    b = m.log(abs(x/y)) + (x**2 + y)**3
if y != 0 and x == 0:
    b = (x**2 + y)**3
if y == 0:
    d = 0

print(f'Значение b = {b}')
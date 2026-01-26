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


if x - y >= 0:
    b = m.sin(x+y) + 2 * (x+y)**2
if x - y < 0:
    b = m.sin(x-y) + (x-y)**3
if x == 0 and y != 0:
    b =  x**2 + m.sqrt(abs(y))
if y == 0:
    d = 0

print(f'Значение b = {b}')
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



if x < y:
    h = m.atan(x + abs(y))
if x > y:
    h = m.atan(abs(x) + y)
if x == y:
    h = (x + y)**2

print(f'Значение h = {h}')

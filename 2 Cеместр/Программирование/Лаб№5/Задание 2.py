print('Программа находит значение выражения.\n')

import math as m
import re

while True:
    x  = input('Введите числовое значение x: ')
    y = input('Введите числовое значение y: ')
    if bool(re.search(r'[-0-9]', x)) and bool(re.search(r'[-0-9]', y)):
        x = int(x)
        y = int(y)
        break
    else:
        print('Ошибка: Введите данные корректно!')


denominator = 0.5 + m.sin(y)**2

if  denominator == 0:
    print('Ошибка: Деление на ноль!')
    exit()
else:
    d = (2 * m.cos(x - m.pi/6) / (denominator)) + (abs(y - x) / 3)
    print(f'Значение d = {d}')
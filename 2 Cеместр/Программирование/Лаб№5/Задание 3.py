print('Программа находит значение выражения.\n')

import math as m
import re

while True:
    x = input('Введите числовое значение x: ')
    y = input('Введите числовое значение y: ')
    z = input('Введите числовое значение z: ')
    if bool(re.search(r'[-0-9]', x)) and bool(re.search(r'[-0-9]', y)) and bool(re.search(r'[-0-9]', z)):
        x = int(x)
        y = int(y)
        z = int(z)
        break
    else:
        print('Ошибка: Введите данные корректно!')


denominator = m.sin(y)**2 - (m.sin(x) * m.sin(y))**2

if  denominator == 0:
    print('Ошибка: Деление на ноль!')
    exit()
else:
    w = ((x/y) * (z+x) * m.e**(abs(x-y)) + m.log(1 + m.e)) / denominator
    print(f'Значение w = {w}')
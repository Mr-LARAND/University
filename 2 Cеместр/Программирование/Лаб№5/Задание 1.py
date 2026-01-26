print('Программа находит значение выражения.\n')

import math as mt
from Check_out import check_digit

x, y, z = check_digit(3)

denominator = z + x**2 / 4

if  denominator == 0:
    print('Ошибка: Деление на ноль!')
    exit()

res = abs((y - (abs(x)) ** 0.5) * (x - (y / (z + x ** 2 / 4))))

if res == 0:
    print('Нет решений !')
else:
    k = mt.log(abs((y - (abs(x))**0.5) * (x - (y /  denominator))))
    print(f'Значение k = {k}')
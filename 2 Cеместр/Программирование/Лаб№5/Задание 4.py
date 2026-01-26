print('Программа находит значение выражения.\n')

import math as m
import Check_out



x, y, z = Check_out.check_digit(3)

denominator = 1 + x**2 * abs(y - m.tan(z))

if  denominator == 0:
    print('Ошибка: Деление на ноль!')
    exit()
else:
    b = (3 + m.e**(y-1)) / denominator
    print(f'Значение b = {b}')
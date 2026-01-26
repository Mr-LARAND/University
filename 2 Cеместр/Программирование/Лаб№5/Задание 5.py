print('Программа находит значение выражения.\n')

import Check_out
import math as m
import re

a, b, c = Check_out.check_digit(3)

if a * b < -2:
    p = m.sqrt(abs(a * b)) + 2 * c
if -2 <= a * b <= 2:
    p = a**3 + b**2 - c**2
if a * b > 2:
    p = a**c - b

print(f'Значение p = {p}')

'''
Ларин Андрей группа 12/2
Лаб№1 Задача 6
Даны катеты прямоугольного треугольника. Найти его гипотенузу.

'''

import math

a = int(input())
b = int(input())

print(int(math.sqrt(a**2+b**2)))

# без math
x = float(input())
y = float(input())
z = (x**2+y**2)**0.5
print(z)


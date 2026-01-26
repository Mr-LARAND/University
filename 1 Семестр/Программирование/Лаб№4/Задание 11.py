'''
Ларин Андрей группа 12/2
Лаб№4 Задача 11
В двумерном массиве хранится информация о зарплате 18 сотрудников фирмы за каждый
месяц года. Определить общую зарплату, выплаченную за год всем сотрудникам фирмы.
Запросить кол-во сотрудников в фирме, диапазон зарплат за месяц, из которого рандомно выбирается зарплата каждого сотрудника.
Определить общую зарплату за год всем сотрудникам фирмы.

'''

import random

while True:
    quantity = input('Введите кол-во сотрудников в фирме: ')
    salary_min = input('Введите минимальную зарплату в месяц: ')
    salary_max = input('Введите максимальную зарплату в месяц: ')
    if all(x.isdigit() for x in (quantity, salary_min, salary_max)):
        quantity = int(quantity)
        salary_min = int(salary_min)
        salary_max = int(salary_max)
        if salary_max > salary_min and quantity != 0:
            break
        else:
            print('Ошибка! Введите числовые данные корректно!')
    else:
        print('Ошибка! Введите только числа (целые, положительные)!')

result = []

for x in range(quantity):
    array = []
    for y in range(1, 12 + 1):
        array.append(random.randint(salary_min, salary_max))
    result.append(array)

summa = 0

for cnt, elem in enumerate(result):
    summa += sum(elem)
    print(f'Общая зарплата за год сотрудника №{cnt + 1}: {summa}')
    summa = 0
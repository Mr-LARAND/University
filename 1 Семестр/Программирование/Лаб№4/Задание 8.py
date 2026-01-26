'''
Ларин Андрей группа 12/2
Лаб№4 Задача 8
В двумерном массиве хранится информация о зарплате 20 человек за каждый месяц года
(первого человека — в первой строке, второго — во второй и т. д.). Составить программу для расчета
общей зарплаты, полученной за год любым человеком, информация о зарплате которого представлена
в массиве. Рассчитайте сколько было выплачено фирмой за каждый месяц года.
Запросить кол-во человек в фирме, диапазон зарплат за месяц, из которого рандомно выбирается
зарплата каждого сотрудника. Запросить номер сотрудника, для которого будет определяться
зарплата за каждый месяц (1 год) и сумма за год.

'''

import random

while True:
    quantity = input('Введите кол-во человек в фирме: ')
    salary_min = input('Введите минимальную зарплату в месяц: ')
    salary_max = input('Введите максимальную зарплату в месяц: ')
    number_human = input('Введите номер сотрудника: ')
    if all(x.isdigit() for x in (quantity, salary_min, salary_max, number_human)):
        quantity = int(quantity)
        salary_min = int(salary_min)
        salary_max = int(salary_max)
        number_human = int(number_human)
        if salary_max > salary_min and quantity >= number_human:
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

month = 0
summa = 0

for salary in result[number_human - 1]:
    month += 1
    summa += salary
    print(f'Зарплата в {month}-й месяц: {salary}')

print(f'Сумма за год: {summa}')
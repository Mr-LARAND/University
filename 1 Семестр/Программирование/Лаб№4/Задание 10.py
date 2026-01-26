'''
Ларин Андрей группа 12/2
Лаб№4 Задача 10
Фирма имеет 10 магазинов. Информация о доходе каждого магазина за каждый месяц года
хранится в двумерном массиве (первого магазина — в первой строке, второго — во второй и т. д.).
Составить программу для расчета среднемесячного дохода любого магазина.
С клавиатуры вводится число магазинов, диапазон доходов каждого магазина за месяц, из которого рандомно выбирается доход.
Составить программу для расчёта среднемесячного дохода магазина, номер которого запрашивается с клавиатуры.

'''

from random import randint

while True:
    shops = input('Введите кол-во магазинов: ')
    income_min = input('Введите минимальный доход магазина за месяц: ')
    income_max = input('Введите максимальный доход магазина за месяц: ')
    number_shop = input('Введите номер магазина, для которого необходимо рассчитать среднемесячный доход: ')
    if all(x.isdigit() for x in (shops, income_min, income_max)):
        shops = int(shops)
        income_min = int(income_min)
        income_max = int(income_max)
        number_shop = int(number_shop)
        if shops >= number_shop and income_max > income_min and shops + number_shop != 0:
            break
        else:
            print('Ошибка! Введите данные корректно!')
    else:
        print('Ошибка! Введите только числа (целые, положительные)!')

array = []
for x in range(shops):
    months = []
    for y in range(12):
        months.append(randint(income_min, income_max))
    array.append(months)

summa = 0

for month in array[number_shop - 1]:
    summa += month

print(f'Среднемесячный доход магазина №{number_shop}: {int(summa/12)}')
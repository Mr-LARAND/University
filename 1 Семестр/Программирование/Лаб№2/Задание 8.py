'''
Ларин Андрей группа 12/2
Лаб№2 Задача 8
Запрашивается количество дней в месяце (28-31), диапазон температур (не должен
выходить за пределы от -90 до +57 градусов Цельсия). Ежедневная температура находится как
случайное число из заданного пользователем диапазона. На экран выводятся в столбик номера чисел,
когда была отрицательная температура и сколько градусов, например:
1-го числа температура была -5
5-го числа температура была -3
и т.д.

'''
import random, re

while True:
    days = input('Количество дней в месяце: ')
    min_temp = input('Минимальная температура за месяц: ')
    max_temp = input('Максимальная температура за месяц: ')
    if not(bool(re.search(r'[a-z]',days))) and not(bool(re.search(r'[a-z]',min_temp))) and not(bool(re.search(r'[a-z]',max_temp))):
        days = int(days)
        min_temp = int(min_temp)
        max_temp = int(max_temp)
        if min_temp < max_temp:
            break
        else:
            print('Ошибка! Введите диапазон корректно')

    else:
        print("Ошибка! Введите числа (целые)!")

cnt=0

if -90 <= min_temp and max_temp <= 57:
    for x in range(1, days+1):
        day_temp = random.randint(min_temp, max_temp)
        if day_temp < 0:
            print(f'{x}-го числа температура была {day_temp}')
        else:
            cnt += 1
    if cnt == days:
        print('В этом месяце не было отрицательной температуры !')

else:
    print('Температура выходит из допустимого диапазона !')
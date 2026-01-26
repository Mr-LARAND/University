'''
Ларин Андрей группа 12/2
Лаб№4 Задача 3
Дан список a из десяти элементов с числами, среди которых есть отрицательные. Записать все 
отрицательные числа во второй список. Запросить кол-во элементов в списке

'''

from random import randint

while True:
    counter = input('Введите кол-во элементов в списке: ')
    if counter.isdigit():
        counter = int(counter)
        break
    else:
        print('Ошибка! Введите число (целое)!')

a = []
negative = []

for _ in range(counter):
    a.append(randint(-10_000, 10_000))

for char in a:
    if char < 0:
        negative.append(char)

print(f'Исходный список: {a}\nСписок с отрицательными значениями: {negative}')
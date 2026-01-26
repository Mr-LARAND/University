'''
Ларин Андрей группа 12/2
Лаб№4 Задача 4
Дан список. Получить новый список, в котором будут все элементы заданного списка, кроме 
элемента с индексом k.

'''

from random import randint

a = [x for x in range(randint(20,31), randint(35,45))]
print(f'Вот пример списка: {a}')

while True:
    index = input('Введите индекс элемента, который хотите убрать: ')
    if index.isdigit():
        index = int(index) - 1
        break
    else:
        print('Ошибка! Введите число (целое)!')

a.remove(a[index])
# a.pop(index)
print(f'Результат: {a}')
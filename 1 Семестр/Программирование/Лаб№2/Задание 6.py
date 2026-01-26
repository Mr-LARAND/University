'''
Ларин Андрей группа 12/2
Лаб№2 Задача 6
Ввести диапазон учеников в каждом классе, диапазон баллов, количество классов.
Определить среднюю оценку в каждом классе. Количество учащихся в каждом классе и их баллы —
случайные числа в заданных пользователем диапазонах.

'''

print('\nПрограмма считает среднюю оценку в каждом классе\n')

import random

while True:
    min_student = input('Минимальное количество учеников в классе: ')
    max_student = input('Максимальное количество учеников в классе: ')
    min_score = input('Минимальный балл: ')
    max_score = input('Максимальный балл: ')
    classes = input('Количество классов: ')

    if all(x.isdigit() for x in (min_student, max_student, min_score, max_score, classes)):
        max_student = int(max_student)
        min_student = int(min_student)
        max_score = int(max_score)
        min_score = int(min_score)
        classes = int(classes)
        break
    else:
        print('Ошибка! Введите числа (целые)')

for x in range(1, classes + 1):
    num_student = random.randint(min_student, max_student)
    res = [random.randint(min_score, max_score) for _ in range(num_student)]
    score = sum(res) / num_student if num_student > 0 else 0
    print(f"Средний балл в {x} классе = {round(score, 3)}")

'''
Ларин Андрей группа 12/2
Лаб№4 Задача 12
Три группы студентов, в каждой из которых 20 человек, в сессию сдавали по 3 экзамена.
Сведения об оценках каждой группы хранятся в двумерных массивах. Определить лучшую, по средней
оценке, группу.
С клавиатуры запрашивается кол-во групп, диапазон кол-ва студентов в каждой группе,
из которого оно рандомно выбирается, кол-во экзаменов, диапазон баллов, из которого рандомно выбирается оценка.
Определить группу, лучшую по среднему баллу.

'''

from random import  randint

while True:
    num_groups = input("Введите количество групп: ")
    min_students = input("Введите минимальное количество студентов в группе: ")
    max_students = input("Введите максимальное количество студентов в группе: ")
    num_exams = input("Введите количество экзаменов: ")
    min_score = input("Введите минимальную оценку: ")
    max_score = input("Введите максимальную оценку: ")
    if all(x.isdigit() for x in (num_groups, min_students, max_students, num_exams, min_score, max_score)):
        num_groups = int(num_groups)
        min_students = int(min_students)
        max_students = int(max_students)
        num_exams = int(num_exams)
        min_score = int(min_score)
        max_score = int(max_score)
        if max_students > min_students and max_score > min_score:
            break
        else:
            print('Ошибка! Введите данные корректно!')
    else:
        print('Ошибка! Введите только числа (целые, положительные)!')

average_scores = []

for i in range(num_groups):
    num_students = randint(min_students, max_students)
    group = []

    for _ in range(num_students):
        student_scores = [randint(min_score, max_score) for _ in range(num_exams)]
        group.append(student_scores)

    total_score = 0
    for student_scores in group:
        total_score += sum(student_scores)

    average_score = total_score / (num_students * num_exams)
    average_scores.append((i + 1, average_score))

    print(f"Группа {i + 1}: средний балл = {average_score:.2f}")

best_group = max(average_scores, key=lambda x: x[1])

print(f"Лучшая группа: Группа {best_group[0]}, средний балл = {best_group[1]:.2f}")

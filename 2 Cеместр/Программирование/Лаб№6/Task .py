'''
2. Расположить столбцы матрицы D[M, N] в порядке возрастания элементов k-й
 строки (1 <= k <= М).
'''

from random import randint
from Check_out import check_digit


COUNT = 2 # Кол-во переменных, которые необходимо сгенерировать
M, N = check_digit(COUNT)

print('\nИсходная матрица:')
# генерация матрицы
matrix_2 = []
for i in range(M):
    elem_matrix = []
    for j in range(N):
        elem_matrix.append(randint(0,10))
        print(elem_matrix[j], end=' ')
    matrix_2.append(elem_matrix)
    print()

# Ввод номера строки k для сортировки
while True:
    try:
        k = int(input(f'Введите номер строки k (1 <= k <= {M}): ')) - 1
        if 0 <= k < M:
            break
        else:
            print(f"Номер строки должен быть от 1 до {M}.")
    except ValueError:
        print("Ошибка ввода. Пожалуйста, введите целое число.")

# Сортировка столбцов по элементам k-й строки
sorted_columns = sorted(zip(*matrix_2), key=lambda x: x[k])

matrix_2 = list(map(list, zip(*sorted_columns)))

print(f'\nМатрица после сортировки столбцов по элементам, {k + 1}-й строки:')
for i in matrix_2:
    print(' '.join(map(str, i)))
'''
Ларин Андрей группа 12/2
Лаб№7 Задача 6
1. Дана целочисленная квадратная матрица. Найти в каждой строке наибольший
 элемент и в каждом столбце наименьший. Вывести на экран.
 2. Дана действительная квадратная матрица порядка N (N — нечетное), все
 элементы которой различны. Найти наибольший элемент среди стоящих на
 главной и побочной диагоналях и поменять его местами с элементом, стоящим
 на пересечении этих диагоналей.
'''
import Utilities as ut

print('Программа находит в каждой строке наибольший элемент и в каждом столбце наименьший\n'
      'Необходимо задать порядок квадратной матрицы:')

COUNT = 1  # Кол-во переменных, которые необходимо сгенерировать
N = ut.check_digit(COUNT)[0]

print('\nИсходная матрица:')
# генерация матрицы
matrix_1 = ut.get_integer_matrix(N, N, 0, 10)
ut.print_matrix(matrix_1)

print()
# Нахождение наибольшего в строке
cnt = 0
dictionary = {}
for x in matrix_1:
    dictionary[*x] = ut.get_max(x)
    cnt += 1
    print(f'В {cnt}-й строке наибольший элемент: {dictionary[*x]}')

print()
# Нахождение наименьшего в столбце
min_elem = float('inf')
for indx in range(len(x)):
    for x in matrix_1:
        if  x[indx] < min_elem:
            min_elem = x[indx]
    print(f'В {indx + 1}-ом столбце наименьший элемент: {min_elem}')



print('\nДалее программа находит наибольший элемент среди стоящих на\n'
      'главной и побочной диагонали и меняет его местами с элементом,\n'
      'стоящим на пересечении этих диагоналей\n'
      'Необходимо задать порядок квадратной матрицы (Порядок должен быть нечетным):')

COUNT = 1 # Кол-во переменных, которые необходимо сгенерировать
N = ut.check_digit(COUNT)[0]
N = ut.even_number(N)

print('\nИсходная матрица:')
# генерация матрицы
matrix_2 = ut.get_real_matrix(N, N, 0, 10)
ut.print_matrix(matrix_2)

# Находим наибольший элемент на глав/поб диагоналях
elem_max = matrix_2[0][0]
str_index, post_index = 0, 0

for i in range(N):
    for j in range(N):
        if (i == j or i + j == N - 1) and matrix_2[i][j] > elem_max:
            elem_max = matrix_2[i][j]
            str_index, post_index = i, j

center_i = center_j = N // 2
matrix_2[str_index][post_index], matrix_2[center_i][center_j] = matrix_2[center_i][center_j], matrix_2[str_index][post_index]

print('\nИзменённая матрица:')
ut.print_matrix(matrix_2)
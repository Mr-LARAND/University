'''
Ларин Андрей группа 12/2
Лаб№7 Задача 2
 1. Дана целая квадратная матрица n-го порядка. Определить, является ли она
 магическим квадратом, т. е. такой матрицей, в которой суммы элементов во всех
 строках и столбцах одинаковы.
 2. Дана прямоугольная матрица A[N, N]. Переставить первый и последний
 столбцы местами и вывести на экран.
'''
import Utilities as ut

print('Программа определяет, является лм матрица магическим квадратом\n'
      'Необходимо задать порядок матрицы:')

COUNT = 1 # Кол-во переменных, которые необходимо сгенерировать
N = ut.check_digit(COUNT)[0]

print('\nИсходная матрица:')
# генерация матрицы
matrix_1 = ut.get_integer_matrix(N, N, 0, 10)
ut.print_matrix(matrix_1)

# нахождение суммы строк
magic = True
for i in range(len(matrix_1) - 1):
    if sum(matrix_1[i]) != sum(matrix_1[i+1]):
        magic = False
        break

# нахождение сумм столбцов
if magic:
    for col in range(N):
        col_sum = sum(matrix_1[row][col] for row in range(N))
        if col_sum != sum(matrix_1[0]):
            magic = False
            break

# оптимизированный вариант
if magic:
    target_sum = ut.get_sum(matrix_1[0])  # Сумма первой строки
    for col in range(N):
        col_sum = 0
        for row in range(N):
            col_sum += matrix_1[row][col]
        if col_sum != target_sum:
            magic = False
            break

print('Матрица является магической' if magic else 'Матрица не является магической')


print('Далее программа Переставить первый и последний столбцы местами\n'
      'Необходимо задать порядок матрицы (N, M):')

COUNT = 2 # Кол-во переменных, которые необходимо сгенерировать
N, M = ut.check_digit(COUNT)

print('\nИсходная матрица:')
# генерация матрицы
matrix_2 = ut.get_integer_matrix(N, M, 0, 10)
ut.print_matrix(matrix_2)

print('\nИзменённая матрица:')
for x in matrix_2:
    x[0], x[-1] = x[-1], x[0]
    print(x)
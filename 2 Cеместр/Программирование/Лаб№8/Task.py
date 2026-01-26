print('''
       Программа создаёт числовой массив и сортирует его пятью разными способами:
       сортировка выбором, сортировка вставками, сортировка пузырьками, сортировка слиянием, быстрая сотрировка.
       Результат записывается в файл формата ,xls.
       ''')

from random import *
from time import *

f = open("newfile.xls", "w+")

while True:
    # Ввод данных
    a = input("Введите длинну массива:")
    b = input("Введите начало диапазона случайных чисел:")
    c = input("Введите конец диапазона случайных чисел:")

    # Проверяем входные данные
    if a.isdigit() and int(a) > 0 and b.isdigit() and c.isdigit():
        a = int(a)
        b = int(b)
        c = int(c)
        break
    else:
        print('Ошибка. Введите целые положительные числа')

if b > c:
    print("Начало должно быть меньше конца.")
    exit()

mas = []

f.write('Длинна массива\t%d\n' % (a))
f.write("Диапазон случайных чисел в массиве\t%d\t%d\n" % ((b), (c)))
f.write("Сгенерированный случайным образом массив чисел\t")
for i in range(a):
    mas.append(randint(b, c))
    f.write("%d\t" % mas[i])


def selection_sort(mas):  # сортировка выбором
    for i in range(len(mas)):
        minimum = i
        for j in range(i + 1, len(mas)):
            if mas[j] < mas[minimum]:
                minimum = j
        mas[minimum], mas[i] = mas[i], mas[minimum]
    return mas


def insertion_sort(mas):  # сортировка вставками
    for i in range(len(mas)):
        cursor = mas[i]
        pos = i
        while pos > 0 and mas[pos - 1] > cursor:
            mas[pos] = mas[pos - 1]
            pos = pos - 1
        mas[pos] = cursor
    return mas


def bubble_sort(mas):  # сортировка пузырьками
    def swap(i, j):
        mas[i], mas[j] = mas[j], mas[i]

    n = len(mas)
    swapped = True
    x = -1
    while swapped:
        swapped = False
        x = x + 1
        for i in range(1, n - x):
            if mas[i - 1] > mas[i]:
                swap(i - 1, i)
                swapped = True
    return (mas)


def merge_sort(mas):  # сортировка слиянием
    if len(mas) <= 1:
        return mas
    mid = len(mas) // 2
    left, right = merge_sort(mas[:mid]), merge_sort(mas[mid:])
    return merge(left, right, mas.copy())


def merge(left, right, merged):
    left_cursor, right_cursor = 0, 0
    while left_cursor < len(left) and right_cursor < len(right):

        # Сортируем каждый и помещаем в результат
        if left[left_cursor] <= right[right_cursor]:
            merged[left_cursor + right_cursor] = left[left_cursor]
            left_cursor += 1
        else:
            merged[left_cursor + right_cursor] = right[right_cursor]
            right_cursor += 1
    for left_cursor in range(left_cursor, len(left)):
        merged[left_cursor + right_cursor] = left[left_cursor]
    for right_cursor in range(right_cursor, len(right)):
        merged[left_cursor + right_cursor] = right[right_cursor]
    return merged


def partition(array, begin, end):  # быстрая сортировка
    pivot_idx = begin
    for i in range(begin + 1, end + 1):
        if array[i] <= array[begin]:
            pivot_idx += 1
            array[i], array[pivot_idx] = array[pivot_idx], array[i]
    array[pivot_idx], array[begin] = array[begin], array[pivot_idx]
    return pivot_idx


def quick_sort_recursion(array, begin, end):
    if begin >= end:
        return
    pivot_idx = partition(array, begin, end)
    quick_sort_recursion(array, begin, pivot_idx - 1)
    quick_sort_recursion(array, pivot_idx + 1, end)


def quick_sort(array, begin=0, end=None):
    if end is None:
        end = len(array) - 1

    return quick_sort_recursion(array, begin, end)


f.write("\nСортировка выбором\t")
t1 = perf_counter_ns()
selsort = selection_sort(mas)
t = (perf_counter_ns() - t1) / pow(10, 9)
for i in range(a):
    f.write("%d\t" % selsort[i])
f.write("\nВремя выполнения алгоритма, a\t%f\n" % t)

f.write("Сортировка вставками\t")
t1=perf_counter_ns()
inssort=insertion_sort(mas)
t=(perf_counter_ns() - t1)/pow(10,9)
for i in range(a):
    f.write("%d\t"
%inssort[i])
f.write("\nВремя выполнения алгоритма, a\t%f\n" %t)


f.write("Сортировка пузырьками\t")
t1=perf_counter_ns()
bubble=bubble_sort(mas)
t=(perf_counter_ns() - t1)/pow(10,9)
for i in range(a):
    f.write("%d\t" %bubble[i])
f.write("\nВремя выполнения алгоритма, a\t%f\n" %t)


f.write("Сортировка слиянием\t")
t1=perf_counter_ns()
merge=merge_sort(mas)
t=(perf_counter_ns() - t1)/pow(10,9)
for i in range(a):
    f.write("%d\t" %merge[i])
f.write("\nВремя выполнения алгоритма, a\t%f\n" %t)


f.write("Быстрая сортировка\t")
t1=perf_counter_ns()
quick_sort(mas)
t=(perf_counter_ns() - t1)/pow(10,9)
for i in range(a):
    f.write("%d\t" %mas[i])
f.write("\nВремя выполнения алгоритма, a\t%f\n" %t)

f.close()
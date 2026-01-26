# Сортировка выбором
def find_small_lest(arr): #Функция для нахождения минимального значения(индекса)
    smallest = arr[0]
    smallest_index = 0
    for i in range(1, len(arr)):
        if arr[i] < smallest:
            smallest = arr[i]
            smallest_index = i
    return smallest_index


def selection_sort(arr):
    new_arr = []
    copied_arr = list(arr)
    for i in range(len(copied_arr)):
        smallest = find_small_lest((copied_arr))
        new_arr.append(copied_arr.pop(smallest))
    return new_arr



# Сортировка вставками
def insertion_sort(arr):
    for i in range(len(arr)):
        element = arr[i]
        index = i

        while index > 0 and arr[index - 1] > element:
            arr[index] = arr[index - 1]
            index = index - 1
        arr[index] = element

    return arr



# Сортировка пузырьком
def bubble_sort(arr):
    for i in range(len(arr)):
        swapped = True
        for j in range(0, len(arr)-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
                swapped = False
        if swapped: break
    return arr



# Сортировка слиянием
def merge_list(arr_1, arr_2):  # функция слияния двух отсортированных списков
    result = []
    i = j = 0

    while i < len(arr_1) and j < len(arr_2):
        if arr_1[i] <= arr_2[j]:
            result.append(arr_1[i])
            i += 1
        else:
            result.append(arr_2[j])
            j += 1

    result.extend(arr_1[i:])
    result.extend(arr_2[j:])
    return result


def split_and_merge_list(arr):  # функция деления списка и слияния списков в общий отсортированный список
    if len(arr) <= 1:  # базовый случай рекурсии
        return arr

    mid = len(arr) // 2
    left_arr = split_and_merge_list(arr[:mid])  # рекурсивно сортируем левую половину
    right_arr = split_and_merge_list(arr[mid:])  # рекурсивно сортируем правую половину

    return merge_list(left_arr, right_arr)



# Быстрая сортировка [6, 8, 2, 9, 2, 4, 1]
def quicksort(arr):
    if len(arr) < 2:       # базовый случай, если список длинной 0 или 1
        return arr
    else:
        base = arr[0]      # Ниже описан случай рекурсивного алгоритма

        less = [i for i in arr[1:] if i <= base]
        more = [i for i in arr[1:] if i > base]

        return quicksort(less) + [base] + quicksort(more)
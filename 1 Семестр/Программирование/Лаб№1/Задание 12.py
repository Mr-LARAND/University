'''
Ларин Андрей группа 12/2
Лаб№1 Задача 12
Ввести вещественное число. Вывести на экран его абсолютную величину.

'''

print(abs(float(input('Введите вещественное число: '))))

# Без использования abs
number = float(input('Введите вещественное число: '))
if number < 0:
    module = - number
else:
    module = number
    print(module)

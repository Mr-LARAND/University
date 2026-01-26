'''
Ларин Андрей группа 12/2
Лаб№4 Задача 5
Заполнить список десятью первыми числами последовательности Фибоначчи.
Кол-во чисел последовательности Фибоначчи запросить с клавиатуры

'''

while True:
        data = input('Введите Кол-во чисел последовательности Фибоначчи: ')
        if data.isdigit() and int(data) > 0:
            data = int(data) - 4
            break
        else:
            print('Ошибка! Введите число (целое, положительное)!')

fibonacci = [0, 1]

if data + 4 == 1:
    print(f'Результат: {fibonacci[0]}')
else:
    for x in range(len(fibonacci) + data):
        summa = fibonacci[x] + fibonacci[x+1]
        fibonacci.append(summa)
    print('Результат:', *fibonacci)
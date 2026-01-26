'''
Ларин Андрей группа 12/2
Лаб№3 Задача 5
Составить программу, формирующую строку, состоящую из любого 
заданного количества любых одинаковых символов. 

'''

while True:
    quantity = input('Введите кол-во символов: ')
    symbols = input('Введите символ: ')
    if len(symbols) == 1 :
        if quantity.isdigit():
            quantity = int(quantity)
            break
        else:
            print('Ошибка! Кол-во символов вводится числом(целым)!')
    else:
        print('Ошибка! Введите один символ!')

print(symbols*quantity)
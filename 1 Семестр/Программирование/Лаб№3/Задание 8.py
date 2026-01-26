'''
Ларин Андрей группа 12/2
Лаб№3 Задача 8
Создать программу по подсчету слов, начинающихся на букву А (а).
Нюанс: Ввести текст, запросить любую букву для подсчета слов, начинающихся на нее.

'''

while True:
    text = (''.join(input('Введите текст: ').lower().split()))
    symbol = input('Введите искомую буквку: ').lower()
    if text.isalpha() and symbol.isalpha():
        if len(symbol) == 1:
            break
        print('Ошибка! Введите один символ!')
    else:
        print('Ошибка! Введите только буквы!')

cnt = 0

for word in text:
    if word[0] == symbol:
        cnt += 1
print(f'Слов начинающихся на буквку \"{symbol}\": {cnt}')

'''
Ларин Андрей группа 12/2
Лаб№3 Задача 6
Дано предложение. Напечатать все его буквы и.
Нюанс: Вводится текст; ввести с клавиатуры любой символ для поиска и распечатки всех символов.

'''

while True:
    text = input('Введите предложение: ').lower()
    search_symbol = input("Введите символ для поиска: ").lower()
    if len(text) != 0 and len(search_symbol) != 0:
        break
    else:
        print('Ошибка! поле ввода не может быть пустым!')

result = []
for symbol in text:
    if symbol == search_symbol:
        result.append(symbol)

print(f'Найденные символы: {" ".join(map(str, result))}' if len(result) != 0 else 'В тексте нет данного символа !')

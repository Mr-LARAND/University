'''
Ларин Андрей группа 12/2
Лаб№3 Задача 17
Дано предложение. Определить, сколько в нем гласных букв.

'''

while True:
    text = input('Введите текст: ').lower()
    if len(text) != 0:
        break
    else:
        print('Поле ввода не может быть пустым!')

char = []
letter = 'уеэоаыяиюё'

for x in text:
    if x in letter:
        char.append(x)
print(f'Гласных букв в тексте: {len(char)}')
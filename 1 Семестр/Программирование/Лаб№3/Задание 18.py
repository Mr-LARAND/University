'''
Ларин Андрей группа 12/2
Лаб№3 Задача 18
Создать программу по подсчету всех букв в тексте.

'''

while True:
    text = input('Введите текст: ').lower()
    if len(text) != 0:
        break
    else:
        print('Поле ввода не может быть пустым!')

result = 0

for x in text:
    if x.isalpha():
        result += 1

print(f'Кол-во букв в ведённом тексте равно: {result}')
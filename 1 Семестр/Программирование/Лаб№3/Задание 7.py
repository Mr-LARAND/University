'''
Ларин Андрей группа 12/2
Лаб№3 Задача 7
Дана строка символов (предложение). Заменить во всех словах первую 
букву заглавной. 

'''

while True:
    line = input('Напечатайте предложение: ').lower().split()
    line_glued = ''.join(line)
    if not(line_glued.isdigit()):
        break
    else:
        print('Ошибка! В тексте могут быть только буквы !')

for word in line:
    big_char = word.capitalize()
    print(big_char, end = ' ')

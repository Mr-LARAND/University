'''
Ларин Андрей группа 12/2
Лаб№3 Задача 11
Дана последовательность слов. Проверить, правильно ли в ней записаны
словосочетания жи и ши. Исправить ошибки.

'''

sequence = input('Введите текст: ').lower()

if 'жы' in sequence or 'шы' in sequence:
    for word in range(len(sequence) - 1):
        if sequence[word] + sequence[word + 1] == 'жы' or sequence[word] + sequence[word + 1] == 'шы':
            result = (sequence.replace('жы', 'жи').replace('шы', 'ши'))
    print(f'В тексте исправлены ошибки, финальный текст: {result.capitalize()}')
else:
    print('В тексте нет ошибок \'жи\' \'ши\' !' )
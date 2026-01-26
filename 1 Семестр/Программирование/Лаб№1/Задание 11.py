'''
Ларин Андрей группа 12/2
Лаб№1 Задача 11
Ввести возраст человека и вывести его вместе с последующим словом «год», «года»
или «лет»

'''

age = int(input('Введите возраст: ')) 
if 11 <= age % 100 <= 14:
    print(f'Вам {age} лет')
elif age % 10 == 1:
    print(f'Вам {age} год')
elif age % 10 in [2, 3, 4]:
    print(f'Вам {age} года')
else:
    print(f'Вам {age} лет')

# Выводятся все года от 1 до 100
for age in range(1, 101):
    if 11 <= age % 100 <= 14:
        print(f'Вам {age} лет')
    elif age % 10 == 1:
        print(f'Вам {age} год')
    elif age % 10 in [2, 3, 4]:
        print(f'Вам {age} года')
    else:
        print(f'Вам {age} лет')


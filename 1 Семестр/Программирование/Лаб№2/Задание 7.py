'''
Ларин Андрей группа 12/2
Лаб№2 Задача 7
Программа запрашивает первоначальную сумму вклада (S, руб.), годовой процент (k,
%), срок вклада (n, мес.), проценты начисляются ежемесячно; выводит в столбик:
1-й месяц: сумма вклада ... руб., прирост ... руб.
...
n-й месяц: сумма вклада ... руб., прирост ... руб

'''

print('\nПрограмма вычисляет прибыль с вклада\n')

while True:
    deposit = input('Первоначальная сумма вклада: ')
    percent = input('Годовой процент: ')
    time = input('Срок вклада (мес): ')
    if deposit.isdigit() and percent.isdigit() and time.isdigit():
        deposit = int(deposit)
        percent = int(percent)
        time = int(time)
        break
    else:
        print('Ошибка! Введите числа (целые)!')


for x in range(1, time+1):
    score = deposit*(percent/100) / 12
    print(f'{x}-й месяц: сумма вклада {deposit} руб.', end = ' ')
    deposit += score
    print(f'прирост {score} руб. Результирующий депозит: {deposit}')
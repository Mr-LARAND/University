'''
Ларин Андрей группа 12/2
Лаб№3 Задача 19
Дан текст. Напишите программу, которая его декодирует.
«Ilmujcbec gq y rpcyqspc, zsr npyargac gq rfc icw rm gr» (K->M, O->Q, E->G)

'''

text = input('Введите текст для декодирования (только латинские буквы): ').lower()

while True:
    shift = input("Введите смещение (целое число): ")
    if shift.isdigit():
        shift = int(shift)
        break
    else:
        print("Ошибка! введите целое число!")

decoded = []

for char in text:
    if char in 'qwertyuiopasdfghjklzxcvbnm':
        base = ord('a')
        decoded_char = chr((ord(char) - base + shift) % 26 + base)
        decoded.append(decoded_char)
    else:
        decoded.append(char)

print(f"Декодированный текст: {''.join(decoded)}")
CC = gcc
# -Wall -Wextra: вывод всех предупреждений
# -fPIC: позиционно-независимый код (обязательно для динамических библиотек)
# -I.: искать заголовочные файлы в текущей папке
CFLAGS = -Wall -Wextra -fPIC -I.

# Флаги линковки
LDFLAGS = -lm

# Названия файлов
LIB_NAME = matrix
STATIC_LIB = lib$(LIB_NAME).a
DYNAMIC_LIB = lib$(LIB_NAME).so
EXEC = test_matrix

# Цель по умолчанию (срабатывает просто при вводе 'make')
all: $(STATIC_LIB) $(DYNAMIC_LIB) $(EXEC)

# 1. Компиляция исходного кода библиотеки в объектный файл
matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

# 2. Создание СТАТИЧЕСКОЙ библиотеки
$(STATIC_LIB): matrix.o
	ar rcs $@ $^

# 3. Создание ДИНАМИЧЕСКОЙ библиотеки
$(DYNAMIC_LIB): matrix.o
	$(CC) -shared -o $@ $^ $(LDFLAGS)

# 4. Компиляция объектного файла основной программы
main.o: main.c matrix.h
	$(CC) $(CFLAGS) -c main.c

# 5. Сборка исполняемого файла
# Линкуем с динамической библиотекой (-lmatrix). 
# -Wl,-rpath,. указывает системе искать .so файл прямо в текущей папке при запуске программы.
$(EXEC): main.o $(DYNAMIC_LIB)
	$(CC) -o $@ main.o -L. -l$(LIB_NAME) -Wl,-rpath,. $(LDFLAGS)

# Цель для сборки и сразу запуска программы (как просили в задании)
run: all
	./$(EXEC)

# Цель для удаления всех сгенерированных файлов
clean:
	rm -f *.o *.a *.so $(EXEC)


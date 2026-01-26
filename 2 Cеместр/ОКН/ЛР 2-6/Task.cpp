#include <iostream>
#include <cstdlib>  // для rand() и srand()
#include <ctime>    // для time()

int main() {
    // Инициализация генератора случайных чисел
    std::srand(std::time(0));

    // Ввод размера массива
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    // Создание динамического массива
    int* arr = new int[size];

    // Заполнение массива случайными числами
    for (int i = 0; i < size; ++i) {
        arr[i] = std::rand() % 100;  // случайные числа от 0 до 99
    }

    // Вывод исходного массива
    std::cout << "The original array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Удаление каждого третьего элемента
    int newSize = size;
    for (int i = 2; i < newSize; i += 2) {
        for (int j = i; j < newSize - 1; ++j) {
            arr[j] = arr[j + 1];
        }
        --newSize;
    }

    // Вывод массива после удаления каждого третьего элемента
    std::cout << "The array after deleting every third element: ";
    for (int i = 0; i < newSize; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Добавление нуля после каждого пятого элемента
    int finalSize = newSize + (newSize / 5);
    int* finalArr = new int[finalSize];
    int index = 0;

    for (int i = 0; i < newSize; ++i) {
        finalArr[index++] = arr[i];
        if ((i + 1) % 5 == 0) {
            finalArr[index++] = 0;
        }
    }

    // Вывод финального массива
    std::cout << "The final array: ";
    for (int i = 0; i < finalSize; ++i) {
        std::cout << finalArr[i] << " ";
    }
    std::cout << std::endl;

    // Освобождение памяти
    delete[] arr;
    delete[] finalArr;

    return 0;
}
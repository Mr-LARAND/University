#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>

using namespace std;

// Функция для создания динамической матрицы
int** createMatrix(int n) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    return matrix;
}

// Функция для заполнения матрицы случайными числами
void fillMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 100 - 50; // случайные числа от -50 до 49
        }
    }
}

// Функция для вывода матрицы на экран
void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
}

// Функция для освобождения памяти, выделенной под матрицу
void deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Функция для вычисления суммы элементов в столбцах без отрицательных элементов
void sumColumnsWithoutNegatives(int** matrix, int n) {
    for (int j = 0; j < n; j++) {
        bool hasNegative = false;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < 0) {
                hasNegative = true;
                break;
            }
            sum += matrix[i][j];
        }
        if (!hasNegative) {
            cout << "The sum of the elements in the column " << j + 1 << ": " << sum << endl;
        }
    }
}

// Функция для вычисления минимума среди сумм модулей элементов диагоналей, параллельных побочной диагонали
int minSumOfDiagonals(int** matrix, int n) {
    int minSum = INT_MAX;

    // Диагонали выше побочной диагонали
    for (int k = 0; k < n; k++) {
        int sum = 0;
        for (int i = 0, j = k; i < n && j >= 0; i++, j--) {
            sum += abs(matrix[i][j]);
        }
        if (sum < minSum) {
            minSum = sum;
        }
    }

    // Диагонали ниже побочной диагонали
    for (int k = 1; k < n; k++) {
        int sum = 0;
        for (int i = k, j = n - 1; i < n && j >= 0; i++, j--) {
            sum += abs(matrix[i][j]);
        }
        if (sum < minSum) {
            minSum = sum;
        }
    }

    return minSum;
}

int main() {
    srand(time(0)); // инициализация генератора случайных чисел

    int n;
    cout << "Enter the size of the square matrix: ";
    cin >> n;

    // Создание и заполнение матрицы
    int** matrix = createMatrix(n);
    fillMatrix(matrix, n);

    // Вывод исходной матрицы
    cout << "The original matrix:" << endl;
    printMatrix(matrix, n);

    // Вычисление и вывод суммы элементов в столбцах без отрицательных элементов
    cout << "Sums of elements in columns without negative elements:" << endl;
    sumColumnsWithoutNegatives(matrix, n);

    // Вычисление и вывод минимума среди сумм модулей элементов диагоналей, параллельных побочной диагонали
    int minDiagonalSum = minSumOfDiagonals(matrix, n);
    cout << "The minimum among the sums of the modules of the elements of the diagonals parallel to the side diagonal: " << minDiagonalSum << endl;

    // Освобождение памяти
    deleteMatrix(matrix, n);

    return 0;
}
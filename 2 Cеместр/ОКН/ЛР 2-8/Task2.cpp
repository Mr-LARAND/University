#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Шаблонная функция для вычисления F
template <typename T>
T calculateF(T x, T a, T b, T c) {
    if (x < 0 && b != 0) {
        return a - x / (static_cast<T>(10) + b);
    } else if (x > 0 && b == 0) {
        return (x - a) / (x - c);
    } else {
        return static_cast<T>(3) * x + static_cast<T>(2) / c;
    }
}

int main() {
    double a, b, c, x_start, x_end, dx;
    
    cout << "Input a, b, c: ";
    cin >> a >> b >> c;
    cout << "Input X-begin, X-end, dX: ";
    cin >> x_start >> x_end >> dx;
    
    cout << "-------------------------------" << endl;
    cout << "|     x     |      F(x)      |" << endl;
    cout << "-------------------------------" << endl;
    
    // Получаем целые части a, b, c
    int Au = static_cast<int>(a);
    int Bu = static_cast<int>(b);
    int Cu = static_cast<int>(c);
    
    // Проверяем условие для выбора типа
    bool useDouble = ((Au | Bu) & Cu) != 0;
    
    for (double x = x_start; x <= x_end; x += dx) {
        if (useDouble) {
            double result = calculateF<double>(x, a, b, c);
            cout << "| " << setw(9) << x << " | " << setw(14) << result << " |" << endl;
        } else {
            int result = calculateF<int>(static_cast<int>(x), static_cast<int>(a), 
                                       static_cast<int>(b), static_cast<int>(c));
            cout << "| " << setw(9) << static_cast<int>(x) << " | " << setw(14) << result << " |" << endl;
        }
    }
    
    cout << "-------------------------------" << endl;
    
    return 0;
}
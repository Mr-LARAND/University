#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция для вычисления целочисленного значения
int calculateI(int x, int a, int b, int c) {
    if (x < 0 && b != 0) {
        return a - x / (10 + b);
    } else if (x > 0 && b == 0) {
        return (x - a) / (x - c);
    } else {
        return 3 * x + 2 / c;
    }
}

// Функция для вычисления действительного значения
double calculateF(double x, double a, double b, double c) {
    if (x < 0 && b != 0) {
        return a - x / (10.0 + b);
    } else if (x > 0 && b == 0) {
        return (x - a) / (x - c);
    } else {
        return 3.0 * x + 2.0 / c;
    }
}

int main() {
    double a, b, c, x_start, x_end, dx;
    
    cout << "input a, b, c: ";
    cin >> a >> b >> c;
    cout << "input X-beginning, X-end, dX: ";
    cin >> x_start >> x_end >> dx;
    
    cout << "-------------------------------" << endl;
    cout << "|     x     |      F(x)      |" << endl;
    cout << "-------------------------------" << endl;
    
    // Получаем целые части a, b, c
    int Au = static_cast<int>(a);
    int Bu = static_cast<int>(b);
    int Cu = static_cast<int>(c);
    
    bool useDouble = ((Au | Bu) & Cu) != 0; // Условие для выбора типа
    
    for (double x = x_start; x <= x_end; x += dx) 
    {
        if (useDouble) {
            double result = calculateF(x, a, b, c);
            cout << "| " << setw(9) << x << " | " << setw(14) << result << " |" << endl;
        } else {
            int result = calculateI(static_cast<int>(x), static_cast<int>(a), 
                                   static_cast<int>(b), static_cast<int>(c));
            cout << "| " << setw(9) << static_cast<int>(x) << " | " << setw(14) << result << " |" << endl;
        }
    }
    
    cout << "-------------------------------" << endl;
    
    return 0;
}
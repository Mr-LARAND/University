#include <iostream>
#include <cmath> // Для sqrt (квадратного корня)

// Класс Complex представляет комплексное число вида (a + bi)
class Complex {
private:
    double real;      // Действительная часть (a)
    double imaginary; // Мнимая часть (b)

public:
    // Конструкторы (специальные методы для создания объекта)
    
    // 1. Конструктор по умолчанию (без параметров)
    Complex() : real(0), imaginary(0) {} // Число 0 + 0i

    // 2. Конструктор с параметрами
    Complex(double r, double i = 0) : real(r), imaginary(i) {} // Число r + i·i

    // Метод для вычисления модуля комплексного числа |a + bi| = √(a² + b²)
    double abs() const {
        return sqrt(real * real + imaginary * imaginary);
    }

    // Перегрузка операторов (чтобы работать с Complex как с обычными числами)
    // Оператор сложения: (a + bi) + (c + di) = (a + c) + (b + d)i
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }
    
    // Оператор вычитания: (a + bi) - (c + di) = (a - c) + (b - d)i
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }
    
    // Оператор умножения: (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
    Complex operator*(const Complex& other) const {
        return Complex(
            real * other.real - imaginary * other.imaginary,
            real * other.imaginary + imaginary * other.real
        );
    }
    
    // Оператор деления: (a + bi)/(c + di) = [(ac + bd) + (bc - ad)i] / (c² + d²)
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        return Complex(
            (real * other.real + imaginary * other.imaginary) / denominator,
            (imaginary * other.real - real * other.imaginary) / denominator
        );
    }
    
    // Операторы сравнения (сравниваем по модулю)
    bool operator<(const Complex& other) const 
    {
        return abs() < other.abs();
    }
    
    bool operator>(const Complex& other) const 
    {
        return abs() > other.abs();
    }
    
    // Операторы равенства (сравниваем действительные и мнимые части)
    bool operator==(const Complex& other) const 
    {
        return real == other.real && imaginary == other.imaginary;
    }
    
    bool operator!=(const Complex& other) const 
    {
        return (real != other.real) || (imaginary != other.imaginary);
    }
    
   // Метод для вывода комплексного числа в консоль
   void print() const 
   {
    std::cout << real;
    if (imaginary >= 0) 
        std::cout << " + " << imaginary << "i";
    else 
        std::cout << " - " << -imaginary << "i";
}
};

int main() {
    // Создаём два комплексных числа
    Complex a(3, 4);  // 3 + 4i
    Complex b(1, -2); // 1 - 2i
    
    std::cout << "a = ";
    a.print();
    std::cout << std::endl;
    
    std::cout << "b = ";
    b.print();
    std::cout << std::endl;
    
    std::cout << "\na + b = ";
    (a + b).print();
    std::cout << std::endl;
    
    std::cout << "a - b = ";
    (a - b).print();
    std::cout << std::endl;
    
    std::cout << "a * b = ";
    (a * b).print();
    std::cout << std::endl;
    
    std::cout << "a / b = ";
    (a / b).print();
    std::cout << std::endl;
    
    std::cout << "\na < b: " << (a < b) << std::endl;
    std::cout << "a > b: " << (a > b) << std::endl;
    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "a != b: " << (a != b) << std::endl;
    
    return 0;
}
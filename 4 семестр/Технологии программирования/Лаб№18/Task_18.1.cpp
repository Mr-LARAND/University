/*
Вариант 5.
Класс. Прямая.
Члены класса. Координаты двух точек (x1 , y1 ) и (x2 , y2 ).
Методы. Конструктор, деструктор, метод вывода уравнения прямой.
Операторы перегрузки. Проверка параллельности 2-х прямых (*),
определение угла между 2-мя прямыми (%).
Исходные данные. Прямая AB: A(xa , ya ), B(xb , yb ) Прямая CD: C(xc , yc ),
D(xd , yd ).
Результаты. Вывести уравнения прямых линий. Если прямые не парал-
лельны, то найти и вывести угол между ними.
*/
#include <iostream>
#include <cmath>

using namespace std;

class Line {
private:
    double x1, y1; // Координаты первой точки
    double x2, y2; // Координаты второй точки

public:
    Line(double x1 = 0, double y1 = 0, double x2 = 0, double y2 = 0) : x1(x1), y1(y1), x2(x2), y2(y2) 
        { }

    // Деструктор
    ~Line() 
    {}

    // Метод вывода уравнения прямой
    // Общее уравнение прямой: Ax + By + C = 0
    // A = y2 - y1, B = x1 - x2, C = x2*y1 - x1*y2
    void printEquation() const {
        double A = y2 - y1;
        double B = x1 - x2;
        double C = x2 * y1 - x1 * y2;

        cout << A << "*x + (" << B << ")*y + (" << C << ") = 0" << endl;
    }

    // Перегрузка оператора * для проверки параллельности
    // Прямые параллельны, если A1/A2 = B1/B2, т.е. A1*B2 - A2*B1 = 0
    bool operator*(const Line& other) const {
        double A1 = y2 - y1;
        double B1 = x1 - x2;
        
        double A2 = other.y2 - other.y1;
        double B2 = other.x1 - other.x2;
        
        return abs(A1 * B2 - A2 * B1) < 1e-9;
    }

    // Перегрузка оператора % для определения угла между прямыми (в градусах)
    double operator%(const Line& other) const {
        // Направляющий вектор 1: {dx1, dy1}
        double dx1 = x2 - x1;
        double dy1 = y2 - y1;
        
        // Направляющий вектор 2: {dx2, dy2}
        double dx2 = other.x2 - other.x1;
        double dy2 = other.y2 - other.y1;

        // Скалярное произведение
        double dotProduct = dx1 * dx2 + dy1 * dy2;
        
        // Длины векторов
        double mag1 = sqrt(dx1 * dx1 + dy1 * dy1);
        double mag2 = sqrt(dx2 * dx2 + dy2 * dy2);

        // Защита от деления на 0 (если точки прямой совпадают)
        if (mag1 == 0 || mag2 == 0) return 0.0;

        // Косинус угла
        double cosTheta = dotProduct / (mag1 * mag2);
        
        // Защита от выхода за пределы [-1, 1] из-за погрешности вычислений
        if (cosTheta > 1.0) cosTheta = 1.0;
        if (cosTheta < -1.0) cosTheta = -1.0;

        // Находим острый угол между прямыми
        double angleRad = acos(abs(cosTheta)); 
        
        // Переводим радианы в градусы
        double angleDeg = angleRad * 180.0 / M_PI;

        return angleDeg;
    }
};

int main() 
{

    double xa, ya, xb, yb;
    double xc, yc, xd, yd;

    cout << "Ввод данных для прямой AB" << endl;
    cout << "Введите координаты точки A (xa ya): ";
    cin >> xa >> ya;
    cout << "Введите координаты точки B (xb yb): ";
    cin >> xb >> yb;

    cout << "\nВвод данных для прямой CD" << endl;
    cout << "Введите координаты точки C (xc yc): ";
    cin >> xc >> yc;
    cout << "Введите координаты точки D (xd yd): ";
    cin >> xd >> yd;

    // Создание объектов прямых
    Line AB(xa, ya, xb, yb);
    Line CD(xc, yc, xd, yd);

    cout << "\nРезультаты" << endl;
    
    cout << "Уравнение прямой AB: ";
    AB.printEquation();
    
    cout << "Уравнение прямой CD: ";
    CD.printEquation();

    // Проверка параллельности и нахождение угла
    if (AB * CD) 
        cout << "Прямые AB и CD параллельны!" << endl;
    else {
        cout << "Прямые AB и CD не параллельны." << endl;
        double angle = AB % CD;
        cout << "Угол между прямыми составляет: " << angle << " градусов." << endl;
    }

    return 0;
}

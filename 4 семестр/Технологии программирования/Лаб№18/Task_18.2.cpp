/*
Вариант 5.
Создать класс четырехугольник, члены класса – координаты 4-х точек.
Предусмотреть в классе методы проверки существования четырехуголь-
ника вычисления и вывода сведений о фигуре – длины сторон, диагоналей,
периметр, площадь. Создать производный класс – параллелограмм,
предусмотреть в классе проверку, является ли фигура параллелограм-
мом. Написать программу, демонстрирующую работу с классом: дано
N четырехугольников и M параллелограммов, найти среднюю площадь
N четырехугольников и параллелограммы наименьшей и наибольшей
площади.
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const double EPS = 1e-9;

struct Point {
    double x{}, y{};
};

// Сравнения с учётом погрешности
static bool nearlyEqual(double a, double b) {
    return fabs(a - b) < EPS;
}

// Совпадают ли 2 точки приближённо
static bool samePoint(const Point& a, const Point& b) {
    return nearlyEqual(a.x, b.x) && nearlyEqual(a.y, b.y);
}

// Определение операций
static Point operator-(const Point& a, const Point& b) {
    return {a.x - b.x, a.y - b.y};
}

static double cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

static double cross(const Point& a, const Point& b, const Point& c) {
    return cross(b - a, c - a);
}

static double dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

// евклидово расстояние между двумя точками
static double dist(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y); /// метод вычисляет длинну гипотенузы
}

// Проверка принадлежности точки отрезку
static bool onSegment(const Point& a, const Point& b, const Point& p) {
    return nearlyEqual(cross(a, b, p), 0.0) &&
           min(a.x, b.x) - EPS <= p.x && p.x <= max(a.x, b.x) + EPS &&
           min(a.y, b.y) - EPS <= p.y && p.y <= max(a.y, b.y) + EPS;
}

// Ориентация тройки точки
static int orientation(const Point& a, const Point& b, const Point& c) {
    double val = cross(a, b, c);
    if (fabs(val) < EPS) return 0;
    return (val > 0) ? 1 : -1;
}

// Проверка пересечения двух отрезков
static bool segmentsIntersect(const Point& p1, const Point& q1,
                              const Point& p2, const Point& q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(p1, q1, p2)) return true;
    if (o2 == 0 && onSegment(p1, q1, q2)) return true;
    if (o3 == 0 && onSegment(p2, q2, p1)) return true;
    if (o4 == 0 && onSegment(p2, q2, q1)) return true;

    return false;
}

// класс четиырехугольник
class Quadrilateral {
public:
    Point p[4];

    Quadrilateral() = default;

    Quadrilateral(const Point& a, const Point& b, const Point& c, const Point& d) {
        p[0] = a; p[1] = b; p[2] = c; p[3] = d;
    }

    virtual ~Quadrilateral() = default;

// Методы вычисления характеритик
    double side(int i) const {
        return dist(p[i], p[(i + 1) % 4]);
    }

// Длина стороны между вершинами
    double diagonal1() const {
        return dist(p[0], p[2]);
    }

    double diagonal2() const {
        return dist(p[1], p[3]);
    }

// диагонали. первая между 0 и 2 вторая между 1 и 3.
    double perimeter() const {
        return side(0) + side(1) + side(2) + side(3);
    }

    double area() const {
        double s = 0.0;
        for (int i = 0; i < 4; ++i) {
            int j = (i + 1) % 4;
            s += p[i].x * p[j].y - p[j].x * p[i].y;
        }
        return fabs(s) / 2.0;
    }

// проверка валидности четырехугольтника
    bool isValid() const {
        // Нельзя иметь совпадающие точки
        for (int i = 0; i < 4; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                if (samePoint(p[i], p[j])) return false;
            }
        }

        // Нельзя иметь три подряд лежащие на одной прямой точки
        for (int i = 0; i < 4; ++i) {
            if (fabs(cross(p[i], p[(i + 1) % 4], p[(i + 2) % 4])) < EPS)
                return false;
        }

        // Самопересечение: стороны (0,1) и (2,3), а также (1,2) и (3,0)
        if (segmentsIntersect(p[0], p[1], p[2], p[3])) return false;
        if (segmentsIntersect(p[1], p[2], p[3], p[0])) return false;

        // Площадь не должна быть нулевой
        if (area() < EPS) return false;

        return true;
    }

    virtual void printInfo() const {
        cout << "Четырехугольник:\n";
        cout << "  Стороны: "
             << side(0) << ", " << side(1) << ", "
             << side(2) << ", " << side(3) << "\n";
        cout << "  Диагонали: " << diagonal1() << ", " << diagonal2() << "\n";
        cout << "  Периметр: " << perimeter() << "\n";
        cout << "  Площадь: " << area() << "\n";
        cout << "  Существует: " << (isValid() ? "да" : "нет") << "\n";
    }
};
// тут наследование
class Parallelogram : public Quadrilateral {
public:
    Parallelogram() = default;

    Parallelogram(const Point& a, const Point& b, const Point& c, const Point& d) : Quadrilateral(a, b, c, d) {}

// валидность параллелограмма
    bool isParallelogram() const {
        if (!isValid()) 
            return false;

        Point v1 = p[1] - p[0];
        Point v2 = p[2] - p[1];
        Point v3 = p[3] - p[2];
        Point v4 = p[0] - p[3];

        // Противоположные стороны параллельны
        bool firstPairParallel = fabs(cross(v1, v3)) < EPS;
        bool secondPairParallel = fabs(cross(v2, v4)) < EPS;

        return firstPairParallel && secondPairParallel;
    }

    void printInfo() const override 
    {
        cout << "Параллелограмм:\n";
        cout << "  Стороны: "
             << side(0) << ", " << side(1) << ", "
             << side(2) << ", " << side(3) << "\n";
        cout << "  Диагонали: " << diagonal1() << ", " << diagonal2() << "\n";
        cout << "  Периметр: " << perimeter() << "\n";
        cout << "  Площадь: " << area() << "\n";
        cout << "  Существует: " << (isValid() ? "да" : "нет") << "\n";
        cout << "  Является параллелограммом: " << (isParallelogram() ? "да" : "нет") << "\n";
    }
};

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<Quadrilateral> quads;
    vector<Parallelogram> paras;

    quads.reserve(N);
    paras.reserve(M);

    cout << fixed << setprecision(6);

    // Ввод N четырехугольников
    for (int i = 0; i < N; ++i) {
        Point a, b, c, d;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
        quads.emplace_back(a, b, c, d);
    }

    // Ввод M параллелограммов
    for (int i = 0; i < M; ++i) {
        Point a, b, c, d;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
        paras.emplace_back(a, b, c, d);
    }

    // Средняя площадь N четырехугольников
    double sumArea = 0.0;
    int validQuads = 0;

    cout << "\nЧетырехугольники\n";
    for (int i = 0; i < (int)quads.size(); ++i) {
        cout << "\nФигура " << (i + 1) << ":\n";
        quads[i].printInfo();

        if (quads[i].isValid()) {
            sumArea += quads[i].area();
            ++validQuads;
        }
    }

    if (validQuads > 0) 
        cout << "\nСредняя площадь четырехугольников: " << sumArea / validQuads << "\n";
    else 
        cout << "\nНет корректных четырехугольников для вычисления средней площади.\n";

    // Поиск параллелограммов наименьшей и наибольшей площади
    cout << "\nПараллелограммы\n";

    int minIdx = -1, maxIdx = -1;

    for (int i = 0; i < (int)paras.size(); ++i) 
    {
        cout << "\nФигура " << (i + 1) << ":\n";
        paras[i].printInfo();

        if (!paras[i].isParallelogram()) continue;

        if (minIdx == -1 || paras[i].area() < paras[minIdx].area()) 
            minIdx = i;
        if (maxIdx == -1 || paras[i].area() > paras[maxIdx].area()) 
            maxIdx = i;
        
    }

    if (minIdx != -1) {
        cout << "\nПараллелограмм с наименьшей площадью:\n";
        paras[minIdx].printInfo();
    } 
    else
        cout << "\nНет корректных параллелограммов.\n";

    if (maxIdx != -1) {
        cout << "\nПараллелограмм с наибольшей площадью:\n";
        paras[maxIdx].printInfo();
    }

    return 0;
}
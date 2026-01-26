#include <iostream>
#include <cstring>

class Library {
private:
    char* name; // указатель на строку с названием книги (выделяется динамически)
    char* author; //  указатель на строку с именем автора (выделяется динамически)
    float price; // Цена книги

public:

    // Конструктор без параметров
    Library() : name(nullptr), author(nullptr), price(0.0f) // Инициализируем указатели и цену
    {
        std::cout << "Вызван конструктор по умолчанию для объекта " << this << std::endl; // вывод адреса объекта
    }

    // Конструктор с параметрами
    Library(const char* n, const char* a, float p) : price(p) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        
        author = new char[strlen(a) + 1];
        strcpy(author, a);
        
        std::cout << "Вызван конструктор с параметрами для объекта " << this << std::endl;
    }

    // Деструктор (Чистим память и выводим сообщение)
    ~Library() {
        delete[] name;
        delete[] author;
        std::cout << "Вызван деструктор для объекта " << this << std::endl;
    }

    // Получаем значение полей
    const char* getName() const { return name; }
    const char* getAuthor() const { return author; }
    float getPrice() const { return price; }

    // Изменяем значение полей
    void setName(const char* n) {
        delete[] name;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }

    void setAuthor(const char* a) {
        delete[] author;
        author = new char[strlen(a) + 1];
        strcpy(author, a);
    }

    void setPrice(float p) { price = p; }

    // Метод для вывода информации
    void display() const {
        std::cout << "Книга: " << (name ? name : "N/A") 
                  << ", Автор: " << (author ? author : "N/A") 
                  << ", Цена: " << price << std::endl;
    }
};

int main() {
    // Создание объекта в статической памяти
    std::cout << "Создание объекта в статической памяти:" << std::endl;
    Library book1;
    book1.setName("Война и мир");
    book1.setAuthor("Лев Толстой");
    book1.setPrice(1500.50f);
    book1.display();
    std::cout << std::endl;

    // Создание объекта в динамической памяти
    std::cout << "Создание объекта в динамической памяти:" << std::endl;
    Library* book2 = new Library("Преступление и наказание", "Фёдор Достоевский", 1200.75f);
    book2->display();
    std::cout << std::endl;

    // Создание массива объектов
    std::cout << "Создание массива объектов:" << std::endl;
    Library books[3] = {
        Library("1984", "Джордж Оруэлл", 950.0f),
        Library("Мастер и Маргарита", "Михаил Булгаков", 1100.0f),
        Library()
    };
    books[2].setName("Анна Каренина");
    books[2].setAuthor("Лев Толстой");
    books[2].setPrice(1300.0f);
    
    for (int i = 0; i < 3; ++i) {
        books[i].display();
    }
    std::cout << std::endl;

    // Удаление объекта из динамической памяти
    std::cout << "Удаление объекта из динамической памяти:" << std::endl;
    delete book2;
    std::cout << std::endl;

    // Автоматическое удаление объектов при выходе из области видимости
    std::cout << "Завершение программы, автоматическое удаление объектов..." << std::endl;
    return 0;
}
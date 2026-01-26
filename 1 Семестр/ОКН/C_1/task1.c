#include <stdio.h>
#include <locale.h>
#include <math.h>

int main()
{
    float b;
    int x = 1, y = 4, z = 3;
    setlocale(LC_ALL, "Rus");
    b = (1 + cos(y - 2))/(sqrt(pow(x,4)/2 + pow(sin(z), 2)) + 5);
    printf("Ответ: b=%f", b);
    return 0;
}
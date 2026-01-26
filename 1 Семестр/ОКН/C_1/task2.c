#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <locale.h> 
int main() 
{ 
    int x; 
    float y;
    x = -231;
    setlocale(LC_ALL,"Rus"); 
    if (x>2) y = x/(4 + exp(sin(x))); 
    else if (x >= 1 && x <= 2 ) y = 2*x + 7; 
    else (x < 1); y = pow(sin(3.14/8.), 2);
    printf("Ответ: y=%f",y); 
    return 0; 
}
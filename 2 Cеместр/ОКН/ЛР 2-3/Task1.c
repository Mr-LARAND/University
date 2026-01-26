#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool entry(int a[], int b[], int sizeA, int sizeB) 
{
    for (int i = 0; i < sizeB; i++) 
    {
        bool found = false;
        for (int j = 0; j < sizeA; j++) 
        {
            if (b[i] == a[j]) 
            {
                found = true;
                break;
            }
        }
        if (!found) 
        {
            return false;
        }
    }
    return true;
}



int main() {
    const int ONCE = 25; // размер b рандомный вводим
    int a[25];
    int b[ONCE];
    srand(time(0));

    for (int i = 0; i < 25; i++) {
        a[i] = rand() % 100 + 1;
    }


    for (int i = 0; i < ONCE; i++) {
        b[i] = rand() % 100 + 1;
    }

    if (entry(a, b, 25, ONCE)) 
    {
        printf("Yes\n");
    } 
    else 
    {
        printf("No\n");
    }

    return 0;
}

/*
Необходимо написать программу для решения следующей задачи. Из
произвольной клетки шахматной доски необходимо найти такой путь на
ней, чтобы конь смог обойти все ее клетки, не попав ни в одну дважды.
Шахматная доска имеет размер 8 x 8. Конь двигается на две клетки по
вертикали и затем на одну клетку по горизонтали, или наоборот, на две
клетки по горизонтали и на одну клетку по вертикали.
*/

#include <stdio.h>

#define MAXDIM 25

// Фиксированная матрица D приращение ходов коня
// Этот порядок обеспечивает обход 8x8 с любого поля
int dx[8] = { 2,  1, -1, -2, -2, -1,  1,  2 };
int dy[8] = { 1,  2,  2,  1, -1, -2, -2, -1 };

// Ф-я подсчёта доступности клетки 
int access(int dim, int x, int y, int board[][MAXDIM]) 
{
    int count = 0;
    for (int k = 0; k < 8; k++) 
    {
        int u = x + dx[k];
        int v = y + dy[k];
        if (u >= 0 && u < dim && v >= 0 && v < dim && board[u][v] == 0)
            count++;
    }
    return count;
}

// Ф-я D-алгоритма (Улучшение правила Варнсдорфа)
void vans(int dim, int x, int y, int board[][MAXDIM], int cnt_step) 
{
    if (cnt_step == dim * dim) 
        return;              

    int min_deg = 9;                      // минимальная доступность
    int best_x = -1, best_y = -1;
    int best_k = -1;                      // для разрешения ничьих по левому столбцу D

    for (int k = 0; k < 8; k++) 
    {         // перебираем в порядке D
        int a = x + dx[k];
        int b = y + dy[k];
        if (a >= 0 && a < dim && b >= 0 && b < dim && board[a][b] == 0) 
        {
            int deg = access(dim, a, b, board);
            if (deg < min_deg || (deg == min_deg && k < best_k)) 
            {
                min_deg = deg;
                best_x = a;
                best_y = b;
                best_k = k;
            }
        }
    }

    if (best_x == -1) 
        return;            

    board[best_x][best_y] = cnt_step + 1;
    vans(dim, best_x, best_y, board, cnt_step + 1);
}

// Ф-я заполнения доски нулями и 
void clockw(int dim, int x, int y, int board[][MAXDIM]) 
{
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            board[i][j] = 0;

    board[x][y] = 1;                       
    vans(dim, x, y, board, 1);         
}

int main() 
{
    int dimension, x, y;
    printf("Введите размер доски: ");
    scanf("%d", &dimension);
    printf("Введите начальную позицию: a,b: ");
    scanf("%d %d", &x, &y);

    int board[MAXDIM][MAXDIM];
    clockw(dimension, x, y, board);

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++)
            printf("%3d", board[i][j]);
        printf("\n");
    }

    return 0;
}
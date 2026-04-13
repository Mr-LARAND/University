/*
Элементы целочисленного массива записать в очередь. Написать
функцию извлечения элементов из очереди до тех пор, пока первый
элемент очереди не станет четным.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int *data;
    int head;
    int tail;
    size_t capacity;
} Queue;

int append(Queue *queue, int value)
{
    if (queue->head >= queue->capacity) {
        queue->capacity *= 2;
        int *new_data = realloc(queue->data, queue->capacity * sizeof(int));
        if (new_data == NULL) {
            printf("Error: 002.\n");
            return 1;
        }
        queue->data = new_data;
    }

    queue->data[queue->tail] = value;
    queue->tail++;
    return 0;
}

int remove_(Queue *queue)
{
    if (queue->tail == queue->head) {
        printf("Очередь пуста!\n");
        return 1;
    }
    
    int value = queue->data[queue->head];
    queue->head++;
    return value;
}

int main() 
{
    // код списка
    int size_arr = 1;
    int lenght = 0;
    int *array = malloc(size_arr * sizeof(int));

    if (array == NULL) {
        printf("Error: 001.\n");
        return 1;
    }

    printf("Введите эелементы массива типа \"int\"\n");
    while (scanf("%d", &array[lenght]) != EOF) {
        lenght++;
        if (lenght >= size_arr) {
            size_arr *= 2;
            array = realloc(array, size_arr * sizeof(int));
            if (array == NULL) {
            printf("Error: 002.\n");
            return 1;
            }
        }
    }

    // код очереди
    Queue *queue = malloc(sizeof(Queue));
    queue->capacity = 2;
    queue->head = 0;
    queue->tail = 0;

    queue->data = malloc(size_arr * sizeof(int));
    if (queue->data == NULL) {
        printf("Error: 001.\n");
        return 1;
    }

    printf("Элемееты очереди:\n");
    for (int i = 0; i < lenght; i++) {
        append(queue, array[i]);
        // queue->data[i] = array[i];
        printf("%d ", queue->data[i]);
    }
    printf("\n");
    free(array);

    while (queue->head < queue->tail && queue->data[queue->head] % 2 != 0) 
        remove_(queue);

    printf("Элемееты очереди после удаления:\n");
    for (int i = queue->head; i < queue->tail; i++)
        printf("%d ", queue->data[i]);
    printf("\n");
    
    return 0;
}

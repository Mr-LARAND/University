/*
Написать функцию, которая оставляет в списке L только первые
вхождения одинаковых элементов.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void append(Node** head_ref, int new_data) 
{
    Node* new_node = malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    Node* last = *head_ref; // Начинаем с головы
    while (last->next != NULL) 
        last = last->next; // Передвигаемся по списку, пока не найдем последний узел
    

    // 5. "Присоединяем" новый узел к хвосту
    // `last` теперь указывает на последний элемент. Меняем его `next`
    last->next = new_node;
}

void print_list(Node* node) 
{
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}


void remove_duplicates(Node* head) 
{
    Node* current = head;
    while (current != NULL) 
    {
        Node* runner = current;
        while (runner->next != NULL) 
        {
            // Если найден дубликат
            if (runner->next->data == current->data) {
                Node* duplicate = runner->next;
                runner->next = runner->next->next;
                free(duplicate);
            } 
            else
                runner = runner->next;
        }
        current = current->next;
    }
}

int main() 
{ 
    Node* head = NULL;

    FILE *file = fopen("data_1.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int value;
    fseek(file, SEEK_SET, 0);
    while (fscanf(file, "%d", &value) == 1) {
        append(&head, value);
    }

    fclose(file);
    printf("Исходный список:\n");
    print_list(head);

    remove_duplicates(head);

    printf("\nСписок после удаления дубликатов:\n");
    print_list(head);

    return 0;
}
